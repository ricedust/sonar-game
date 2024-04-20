#pragma once

#include "Agent.h"
#include "Bullet.h"
#include "ControlSystem.h"
#include "Emitter.h"
#include "GameState.h"
#include "Lifespan.h"
#include "Player.h"
#include "Rigidbody.h"
#include "ofxGui.h"

class GuiSystem {
	Scene& scene;
	EntityView<Agent, Lifespan> agentView{scene.getEntities()};
	EntityView<Bullet, Lifespan> bulletView{scene.getEntities()};
	ofxPanel controlPanel;

   public:
	bool isHidden{false};

	ofxIntSlider maxPlayerEnergySlider;
	ofxFloatSlider playerForceSlider;
	ofxFloatSlider playerTorqueSlider;
	ofxFloatSlider playerScaleSlider;

	ofxFloatSlider agentLifespanSlider;
	ofxFloatSlider agentsPerSecondSlider;
	ofxFloatSlider agentForceSlider;
	ofxFloatSlider agentTorqueSlider;

	ofxFloatSlider bulletsPerSecondSlider;
	ofxFloatSlider bulletSpeedSlider;
	ofxFloatSlider bulletLifespanSlider;

	ofxIntSlider difficultySlider;
	ofxToggle primitiveToggle;

	GuiSystem(Scene& scene);
	void applySettings(EntityIndex playerIndex, EntityIndex enemyEmitterIndex,
					   EntityIndex bulletEmitterIndex);
	void applyDifficulty();
	void draw(const GameState state, EntityIndex playerIndex);
};
