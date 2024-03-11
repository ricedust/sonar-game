#pragma once

#include "SceneObject.h"
#include "ofMain.h"

class Agent : public SceneObject {
	float timeAliveSeconds;
	glm::vec3 targetPosition;

   public:
	float speed{0};
	float rotationSpeed{0};

	Agent();
	float getTimeAliveSeconds() const;
	void setTargetPosition(const glm::vec3 &targetPosition);

	void update();
	void draw();
};
