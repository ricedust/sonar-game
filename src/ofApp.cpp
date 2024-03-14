#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	debugMenu.setup();

	ofSetBackgroundColor(ofColor::black);

	// create player as a shared ptr
	player = make_shared<Player>();
	player->nEnergy = player->remainingEnergy = debugMenu.maxPlayerEnergySlider;

	// create new agent emiiter, passing in player as target scene object
	agentEmitter = AgentEmitter{player};
	agentEmitter.nAgents = debugMenu.agentBatchSizeSlider;
	agentEmitter.agentLifespan = debugMenu.agentLifespanSlider;
	agentEmitter.agentSpawnInterval = debugMenu.agentSpawnIntervalSlider;
}

//--------------------------------------------------------------
void ofApp::update() {
	switch (gameManager.getState()) {
		case GameState::preGame:
			break;
		case GameState::inGame:

			// set player values from sliders
			player->nEnergy = debugMenu.maxPlayerEnergySlider;
			// cap remaining energy to max energy
			player->remainingEnergy =
				min(player->remainingEnergy, player->nEnergy);

			player->speed = debugMenu.playerSpeedSlider;
			player->rotationSpeed = debugMenu.playerRotationSpeedSlider;
			player->setScale(glm::vec3{debugMenu.playerScaleSlider});

			// set agent emiiter values from sliders
			agentEmitter.nAgents = debugMenu.agentBatchSizeSlider;
			agentEmitter.agentLifespan = debugMenu.agentLifespanSlider;
			agentEmitter.agentSpawnInterval =
				debugMenu.agentSpawnIntervalSlider;
			agentEmitter.agentSpeed = debugMenu.agentSpeedSlider;
			agentEmitter.agentRotationSpeed =
				debugMenu.agentRotationSpeedSlider;

			// update all scene objects
			player->update();
			agentEmitter.update();

			// evaluate gameover condition
			player->remainingEnergy =
				player->nEnergy - agentEmitter.getCollidedAgentsCount();
			if (player->remainingEnergy <= 0) gameManager.end();

			break;
		case GameState::postGame:
			break;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	debugMenu.draw(gameManager, *player);

	switch (gameManager.getState()) {
		case GameState::preGame:
			ofDrawBitmapString("Press [Spacebar] to start!",
							   ofGetWindowWidth() / 2 - 64,
							   ofGetWindowHeight() / 2);
			ofDrawBitmapString(
				"Press [F3] to toggle the control panel and debug info at any "
				"time.",
				32, ofGetWindowHeight() - 32);
			break;
		case GameState::inGame:
			// draw all scene objects
			player->draw();
			// drawDebug(*player);
			agentEmitter.draw();

			break;
		case GameState::postGame:
			ofDrawBitmapString("Press [Spacebar] to restart!",
							   ofGetWindowWidth() / 2 - 64,
							   ofGetWindowHeight() / 2);
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	// cout << key << "\n";

	// stateless keybinds
	switch (key) {
		case OF_KEY_F3:
			debugMenu.isHidden = !debugMenu.isHidden;
			break;
	}

	// gamestate-dependent keybinds
	switch (gameManager.getState()) {
		case GameState::preGame:
			if (key == ' ') gameManager.start();
			break;
		case GameState::inGame:
			player->evaluateKeyPress(key);
			break;
		case GameState::postGame:
			if (key == ' ') {
				gameManager.start();
				setup();
			}
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (gameManager.getState() == GameState::inGame)
		player->evaluateKeyRelease(key);
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
