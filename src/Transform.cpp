#include "Transform.h"

Transform::Transform(glm::vec3 position, float rotationDegrees, glm::vec3 scale)
	: position{position}, rotationDegrees{rotationDegrees}, scale{scale} {}

glm::mat4 Transform::getMatrix() const {
	auto translationMatrix = glm::translate(glm::mat4(1), position);

	auto rotationMatrix = glm::rotate(
		glm::mat4(1), glm::radians(rotationDegrees), glm::vec3(0, 0, 1));

	auto scaleMatrix = glm::scale(glm::mat4(1), scale);

	return translationMatrix * rotationMatrix * scaleMatrix;
}

std::ostream& operator<<(std::ostream& os, const Transform& transform) {
	return os << "Position: " << glm::to_string(transform.position) << '\n'
			  << "Rotation: " << transform.rotationDegrees << '\n'
			  << "Scale: " << glm::to_string(transform.scale);
}