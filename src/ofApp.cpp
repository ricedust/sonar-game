#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	state = GameState::preGame;

	ofSetBackgroundColor(ofColor::black);

	if (!AudioSystem::isLoaded()) AudioSystem::setup();

	AudioSystem::play(Sound::environment);
	AudioSystem::play(Sound::soundtrack);

	guiSystem.applyDifficulty();

	setupPlayer();
	setupEnemyEmitter();
	setupBulletEmitter();
	setupHud();
	setupScanner();

	agentSystem.onPlayerCollision = [&]() {
		// decrement player energy
		scene.getComponent<Player>(playerIndex).remainingEnergy--;
		AudioSystem::play(Sound::damaged);
		cout << "ouch!" << '\n';
	};
}

void ofApp::setupPlayer() {
	playerIndex = scene.addEntity();
	scene.assignComponent<Player>(
		playerIndex,
		{guiSystem.maxPlayerEnergySlider, guiSystem.maxPlayerEnergySlider});
	scene.assignComponent<Transform>(playerIndex);
	scene.assignComponent<Rigidbody>(playerIndex);
	scene.assignComponent<Collider>(playerIndex, {5.0f});
	scene.assignComponent<Renderer>(playerIndex, {Sprite::dot, {32, 32, 0}});
}

void ofApp::setupEnemyEmitter() {
	enemyEmitterIndex = scene.addEntity();
	scene.assignComponent<Transform>(enemyEmitterIndex);

	// configure emitter component
	Emitter enemyEmitter{};

	// define how enemies should be spawned by emitter
	enemyEmitter.onSpawn = [&](EntityIndex i) {
		// enemies spawn on random point on edge of viewport
		auto spawnPoint{cameraSystem.getCenter() +
						glm::rotateZ(glm::vec3{1, 0, 0}, ofRandom(TWO_PI)) *
							viewportRadius};

		auto spawnAngle{ofRandom(360.0f)};

		scene.assignComponent<Transform>(
			i, {spawnPoint, spawnAngle, glm::vec3{1.5}});

		scene.assignComponent<Rigidbody>(i);
		scene.assignComponent<Collider>(i, {6.0f});
		scene.assignComponent<Agent>(i);
		scene.assignComponent<Lifespan>(i);
		scene.assignComponent<Renderer>(i, {Sprite::dot, {32, 32, 0}, 0});
		scene.assignComponent<Fader>(i, {4});
	};

	scene.assignComponent<Emitter>(enemyEmitterIndex, std::move(enemyEmitter));
}

void ofApp::setupBulletEmitter() {
	bulletEmitterIndex = scene.addEntity();
	scene.assignComponent<Transform>(bulletEmitterIndex);

	Emitter bulletEmitter{};

	bulletEmitter.onSpawn = [&](EntityIndex i) {
		// Note: no transform needed, entites created by emitter already have
		// one
		Rigidbody bulletRigidbody{};
		bulletRigidbody.speedDamping = 1.0f;
		scene.assignComponent<Rigidbody>(i, std::move(bulletRigidbody));
		scene.assignComponent<Collider>(i, {15.0f});
		scene.assignComponent<Bullet>(i);
		scene.assignComponent<Lifespan>(i);
		scene.assignComponent<Renderer>(i, {Sprite::bullet, {32, 32, 0}});

		AudioSystem::play(Sound::shoot);
	};

	scene.assignComponent<Emitter>(bulletEmitterIndex,
								   std::move(bulletEmitter));
}

void ofApp::setupHud() {
	sonarIndex = scene.addEntity();
	scene.assignComponent<Transform>(sonarIndex);
	scene.assignComponent<Renderer>(sonarIndex, {Sprite::sonar, {540, 540, 0}});

	compassIndex = scene.addEntity();
	scene.assignComponent<Transform>(compassIndex);
	scene.assignComponent<Renderer>(compassIndex,
									{Sprite::compass, {540, 540, 0}});
}

void ofApp::setupScanner() {
	scannerIndex = scene.addEntity();
	scene.assignComponent<Transform>(scannerIndex);
	scene.assignComponent<Scanner>(scannerIndex, {-125.0f});

	scene.assignComponent<Renderer>(scannerIndex,
									{Sprite::sonarline, {540, 540, 0}, 180});

	// configure emitter to create a trail effect on the scanner
	Emitter trailEmitter{};
	trailEmitter.particlesPerSecond = 20;
	trailEmitter.onSpawn = [&](EntityIndex i) {
		scene.assignComponent<Scanner>(i);
		scene.assignComponent<Lifespan>(i, {2.0f});
		scene.assignComponent<Renderer>(i,
										{Sprite::sonarline, {540, 540, 0}, 75});
		scene.assignComponent<Fader>(i, {64});
	};

	scene.assignComponent<Emitter>(scannerIndex, std::move(trailEmitter));
}

//--------------------------------------------------------------
void ofApp::update() {
	switch (state) {
		case GameState::preGame:
			break;
		case GameState::inGame: {
			// fetch player transform
			const Transform& playerTransform =
				scene.getComponent<Transform>(playerIndex);

			guiSystem.applySettings(playerIndex, enemyEmitterIndex,
									bulletEmitterIndex);
			renderSystem.primitiveMode = guiSystem.primitiveToggle;

			// orient bullet emitter to player
			scene.getComponent<Transform>(bulletEmitterIndex) = playerTransform;

			controlSystem.update(playerIndex, bulletEmitterIndex);
			agentSystem.update(playerIndex);

			emitterSystem.update();
			bulletSystem.update();
			physicsSystem.update();

			lifespanSystem.update();

			// check for game over
			if (scene.getComponent<Player>(playerIndex).remainingEnergy <= 0)
				state = GameState::postGame;

			// orient sonar, compass, and scanner to player
			scene.getComponent<Transform>(sonarIndex) = playerTransform;
			scene.getComponent<Transform>(compassIndex).position =
				playerTransform.position;  // preserve compass rotation, so
										   // cardinal directions are preserved
			scanSystem.update(scannerIndex, playerTransform);

			fadeSystem.update();
			// orient camera to player
			cameraSystem.update(playerTransform);

			break;
		}
		case GameState::postGame:
			inputSystem.resetAll();
			break;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	guiSystem.draw(state, playerIndex);

	switch (state) {
		case GameState::preGame:
			ofDisableAlphaBlending();
			ofDrawBitmapString("Press [SPACE] to start!",
							   ofGetWindowWidth() / 2 - 128,
							   ofGetWindowHeight() / 2 + 32 * 0);
			ofDrawBitmapString("HOLD [SPACE] to fire.",
							   ofGetWindowWidth() / 2 - 128,
							   ofGetWindowHeight() / 2 + 32 * 2);
			ofDrawBitmapString("[W] and [S] for propulsion.",
							   ofGetWindowWidth() / 2 - 128,
							   ofGetWindowHeight() / 2 + 32 * 3);
			ofDrawBitmapString("[A] and [D] to turn.",
							   ofGetWindowWidth() / 2 - 128,
							   ofGetWindowHeight() / 2 + 32 * 4);
			ofDrawBitmapString("[R] to restart and reapply difficulty preset.",
							   ofGetWindowWidth() / 2 - 128,
							   ofGetWindowHeight() / 2 + 32 * 5);
			ofDrawBitmapString(
				"Press [F3] to toggle the control panel and debug info at any "
				"time.",
				32, ofGetWindowHeight() - 32);
			break;
		case GameState::inGame:
			cameraSystem.begin();

			renderSystem.draw(cameraSystem.getCenter(), viewportRadius - 64);
			// collisionSystem.drawDebug();

			cameraSystem.end();
			break;
		case GameState::postGame:
			ofDisableAlphaBlending();
			ofDrawBitmapString("Press [R] to restart!",
							   ofGetWindowWidth() / 2 - 64,
							   ofGetWindowHeight() / 2);
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	// stateless keybinds
	switch (key) {
		case OF_KEY_F3:
			guiSystem.isHidden = !guiSystem.isHidden;
			break;
		case 'f':
			ofSetFullscreen(!ofGetWindowMode());
			break;
		case 'r':
			scene.reset();
			setup();
			ofResetElapsedTimeCounter();
			break;
	}

	// gamestate-dependent keybinds
	switch (state) {
		case GameState::preGame:

			if (key == ' ') {
				state = GameState::inGame;
				AudioSystem::play(Sound::ping);
			}
			break;

		case GameState::inGame:

			inputSystem.set(key);
			break;

		case GameState::postGame:
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (state == GameState::inGame) inputSystem.reset(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
