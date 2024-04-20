#include "Transform.h"

glm::mat4 getMatrix(const Transform& transform) {
	auto translationMatrix = glm::translate(glm::mat4{1}, transform.position);

	auto rotationMatrix =
		glm::rotate(glm::mat4{1}, glm::radians(transform.rotationDegrees),
					glm::vec3{0, 0, 1});

	auto scaleMatrix = glm::scale(glm::mat4{1}, transform.scale);

	return translationMatrix * rotationMatrix * scaleMatrix;
}

std::ostream& operator<<(std::ostream& os, const Transform& transform) {
	return os << "Position: " << transform.position << '\n'
			  << "Rotation: " << transform.rotationDegrees << '\n'
			  << "Scale: " << transform.scale;
}