#include "GuiSystem.h"

GuiSystem::GuiSystem(Scene& scene) : scene{scene} {
	controlPanel.setup();

	controlPanel.add(
		maxPlayerEnergySlider.setup("Max Player Energy", 3, 0, 10));
	controlPanel.add(playerForceSlider.setup("Player Force", 256, 16, 512));
	controlPanel.add(playerTorqueSlider.setup("Player Torque", 1, 0.5, 8));
	controlPanel.add(playerScaleSlider.setup("Player Scale", 1, 0.1, 10));

	controlPanel.add(agentLifespanSlider.setup("Agent Lifespan", 10, 5, 30));
	controlPanel.add(agentsPerSecondSlider.setup("Agents Per Second", 2, 0, 8));
	controlPanel.add(agentForceSlider.setup("Agent Force", 128, 16, 512));
	controlPanel.add(agentTorqueSlider.setup("Agent Torque", 4, 1, 16));

	controlPanel.add(
		bulletsPerSecondSlider.setup("Bullets Per Second", 4, 0, 8));
	controlPanel.add(bulletSpeedSlider.setup("Bullet Speed", 512, 64, 1024));
	controlPanel.add(bulletLifespanSlider.setup("Bullet Lifespan", 4, 2, 8));

	controlPanel.add(difficultySlider.setup("Difficulty Preset", 2, 1, 3));
	controlPanel.add(primitiveToggle.setup("Render Primitives", false));
}

void drawText(const std::string& text, int lineNumber) {
	ofPushStyle();
	ofSetColor(ofColor::white);

	const int rightMargin = 160;
	const int lineHeight = 16;
	ofDrawBitmapString(text, ofGetWindowWidth() - rightMargin,
					   lineHeight * lineNumber);

	ofPopStyle();
}

void GuiSystem::applySettings(EntityIndex playerIndex,
							  EntityIndex enemyEmitterIndex,
							  EntityIndex bulletEmitterIndex) {
	// CONFIGURE PLAYER
	Player& player{scene.getComponent<Player>(playerIndex)};

	// set player values from sliders
	player.nEnergy = maxPlayerEnergySlider;
	// cap remaining energy to max energy
	player.remainingEnergy = std::min(player.remainingEnergy, player.nEnergy);

	// update player force and torque
	player.forceMagnitude = playerForceSlider;
	player.torqueMagnitude = playerTorqueSlider;

	// apply player scale
	scene.getComponent<Transform>(playerIndex).scale =
		glm::vec3{playerScaleSlider};

	// update enemy emitter rate
	scene.getComponent<Emitter>(enemyEmitterIndex).particlesPerSecond =
		agentsPerSecondSlider;

	// CONFIGURE AGENTS
	for (EntityIndex i : agentView) {
		Agent& agent{scene.getComponent<Agent>(i)};
		Lifespan& lifespan{scene.getComponent<Lifespan>(i)};

		// update agent force and torque
		agent.forceMagnitude = agentForceSlider;
		agent.torqueMagnitude = agentTorqueSlider;

		// update agent lifespan
		lifespan.limitSeconds = agentLifespanSlider;
	}

	// CONFIGURE BULLETS
	scene.getComponent<Emitter>(bulletEmitterIndex).particlesPerSecond =
		bulletsPerSecondSlider;

	for (EntityIndex i : bulletView) {
		scene.getComponent<Bullet>(i).speed = bulletSpeedSlider;
		scene.getComponent<Lifespan>(i).limitSeconds = bulletLifespanSlider;
	}
}

void GuiSystem::applyDifficulty() {
	switch (difficultySlider) {
		case 1:
			maxPlayerEnergySlider = 5;
			playerForceSlider = 200;
			playerTorqueSlider = 1;
			agentsPerSecondSlider = 2;
			agentForceSlider = 128;
			agentTorqueSlider = 4;
			bulletsPerSecondSlider = 5;
			bulletSpeedSlider = 512;
			break;
		case 2:
			maxPlayerEnergySlider = 4;
			playerForceSlider = 200;
			playerTorqueSlider = 1;
			agentsPerSecondSlider = 3;
			agentForceSlider = 128;
			agentTorqueSlider = 4;
			bulletsPerSecondSlider = 4;
			bulletSpeedSlider = 512;
			break;
		case 3:
			maxPlayerEnergySlider = 3;
			playerForceSlider = 200;
			playerTorqueSlider = 1;
			agentsPerSecondSlider = 4;
			agentForceSlider = 256;
			agentTorqueSlider = 4;
			bulletsPerSecondSlider = 4;
			bulletSpeedSlider = 512;
			break;
		default:
			break;
	}
}

void GuiSystem::draw(const GameState state, EntityIndex playerIndex) {
	if (isHidden) return;

	controlPanel.draw();

	std::stringstream framerateText;
	framerateText << "Frame Rate: " << std::fixed << std::setprecision(3)
				  << ofGetFrameRate();
	std::stringstream elapsedTimeTest;
	elapsedTimeTest << "Elapsed Time: " << std::fixed << std::setprecision(3)
					<< ofGetElapsedTimef();

	std::stringstream playerEnergyText;
	Player& player = scene.getComponent<Player>(playerIndex);
	playerEnergyText << "Player Energy: " << player.remainingEnergy << '/'
					 << player.nEnergy;

	std::stringstream gameStateText;
	gameStateText << "Game State: " << (int)state;

	drawText(framerateText.str(), 1);
	drawText(elapsedTimeTest.str(), 2);
	drawText(playerEnergyText.str(), 3);
	drawText(gameStateText.str(), 4);
}