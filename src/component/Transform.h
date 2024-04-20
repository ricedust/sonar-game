#pragma once

#include <iostream>
#include <string>

#include "ofMain.h"

/// @brief A component describing orientation and size in space.
struct Transform {
	glm::vec3 position{};
	float rotationDegrees{};
	glm::vec3 scale{1};

	friend std::ostream& operator<<(std::ostream& os,
									const Transform& transform);
};

// /// @brief Creates a matrix to perform the transform.
// /// @param transform A transform component.
// /// @return A 4D matrix.
glm::mat4 getMatrix(const Transform& transform);