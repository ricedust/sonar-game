#pragma once

#include "SceneObject.h"
#include "ofMain.h"

class Player : public SceneObject {
	bool inputStates[4]{false, false, false, false};

   public:
	int nEnergy{0};
	int remainingEnergy{0};
	float speed{0};
	float rotationSpeed{0};

	Player();

	void update();
	void draw();

	void setScale(const glm::vec3& scale);
	void evaluateKeyPress(const int& key);
	void evaluateKeyRelease(const int& key);
};

enum InputDirection { left, right, up, down };
