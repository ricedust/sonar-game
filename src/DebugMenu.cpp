#include "DebugMenu.h"

void drawText(const std::string &text, int lineNumber) {
	ofPushStyle();
	ofSetColor(ofColor::white);

	const int rightMargin = 160;
	const int lineHeight = 16;
	ofDrawBitmapString(text, ofGetWindowWidth() - rightMargin,
					   lineHeight * lineNumber);

	ofPopStyle();
}

void DebugMenu::setup() {
	controlPanel.setup();

	controlPanel.add(
		maxPlayerEnergySlider.setup("Max Player Energy", 3, 0, 10));
	controlPanel.add(playerSpeedSlider.setup("Player Speed", 256, 0, 512));
	controlPanel.add(
		playerRotationSpeedSlider.setup("Player Rotation Speed", 180, 20, 720));
	controlPanel.add(playerScaleSlider.setup("Player Scale", 1, 0.1, 10));

	controlPanel.add(agentBatchSizeSlider.setup("Agent Batch Size", 1, 1, 20));
	controlPanel.add(agentLifespanSlider.setup("Agent Lifespan", 10, 5, 30));
	controlPanel.add(agentSpawnIntervalSlider.setup("Agent Spawn Interval", 2, 0.5, 5));
	controlPanel.add(agentSpeedSlider.setup("Speed", 128, 32, 512));
	controlPanel.add(agentRotationSpeedSlider.setup("Agent Rotation Speed", 180, 20, 720));
}

void DebugMenu::draw(const GameManager &gameManager, const Player &player) {
	if (isHidden) return;

	controlPanel.draw();

	std::stringstream framerateText;
	framerateText << "Frame Rate: " << std::fixed << std::setprecision(3)
				  << ofGetFrameRate();
	std::stringstream elapsedTimeTest;
	elapsedTimeTest << "Elapsed Time: " << std::fixed << std::setprecision(3)
					<< ofGetElapsedTimef();
	std::stringstream playerEnergyText;
	playerEnergyText << "Player Energy: " << player.remainingEnergy << '/'
					 << player.nEnergy;
	std::stringstream gameStateText;
	gameStateText << "Game State: " << (int)gameManager.getState();

	drawText(framerateText.str(), 1);
	drawText(elapsedTimeTest.str(), 2);
	drawText(playerEnergyText.str(), 3);
	drawText(gameStateText.str(), 4);
}