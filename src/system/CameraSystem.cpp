#include "CameraSystem.h"

CameraSystem::CameraSystem() {
	camera.enableOrtho();
	camera.setPosition(0, 0, 10);
	camera.lookAt(glm::vec3{}, {0, 1, 0});
}

void CameraSystem::update(const Transform& transform) {
	glm::vec3 cameraPosition{transform.position.x, transform.position.y,
							 camera.getZ()};
	camera.setPosition(cameraPosition);

	// rotate camera so that the up direction is aligned with transform
	glm::vec3 up{glm::rotateZ(glm::vec3{0, 1, 0},
							  glm::radians(transform.rotationDegrees))};
	camera.lookAt({cameraPosition.x, cameraPosition.y, 0}, up);
}

void CameraSystem::begin() { camera.begin(); }
void CameraSystem::end() { camera.end(); }

glm::vec3 CameraSystem::getCenter() const {
	return {camera.getX(), camera.getY(), 0};
}