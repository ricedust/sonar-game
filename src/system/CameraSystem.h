#pragma once

#include "ofMain.h"
#include "Transform.h"

class CameraSystem {
	ofCamera camera{};

   public:
	CameraSystem();
	void update(const Transform& transform);
    void begin();
    void end();
	glm::vec3 getCenter() const;
};
