#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <string>

struct Transform {
	glm::vec3 position{0};
	float rotationDegrees{0};
	glm::vec3 scale{1};

	Transform() = default;
	Transform(glm::vec3 position, float rotationDegrees, glm::vec3 scale);

	/// @brief Returns a matrix to represent the current position, rotation, and
	/// scale.
	/// @return A 4D matrix.
	glm::mat4 getMatrix() const;

	friend std::ostream& operator<<(std::ostream& os,
									const Transform& transform);
};
