#pragma once

#include "ofMain.h"
#include <queue>

/// @brief A component that holds kinematic information.
struct Rigidbody {
   public:
	glm::vec3 velocity{};
	glm::vec3 acceleration{};
	std::queue<glm::vec3> forces{};
	float speedDamping{0.4f};

	float angularVelocity{};
	float angularAcceleration{};
	std::queue<float> torques{};
	float rotationDamping{0.4f};
};
