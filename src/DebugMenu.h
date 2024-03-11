#pragma once

#include "GameManager.h"
#include "Player.h"
#include "ofxGui.h"

class DebugMenu {
	ofxPanel controlPanel;

   public:
	bool isHidden{false};

	ofxIntSlider maxPlayerEnergySlider;
	ofxFloatSlider playerSpeedSlider;
	ofxFloatSlider playerRotationSpeedSlider;
	ofxFloatSlider playerScaleSlider;

	ofxIntSlider agentBatchSizeSlider;
	ofxFloatSlider agentLifespanSlider;
	ofxFloatSlider agentSpawnIntervalSlider;
	ofxFloatSlider agentSpeedSlider;
	ofxFloatSlider agentRotationSpeedSlider;

	void setup();
	void draw(const GameManager &gameManager, const Player &player);
};
