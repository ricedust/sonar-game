#include "BulletSystem.h"

BulletSystem::BulletSystem(Scene &scene) : scene{scene} {}

void BulletSystem::update() {
	for (EntityIndex i : view) {
		auto speed{scene.getComponent<Bullet>(i).speed};
		auto heading{glm::rotateZ(
			glm::vec3{0, 1, 0},
			glm::radians(scene.getComponent<Transform>(i).rotationDegrees))};

		scene.getComponent<Rigidbody>(i).velocity = heading * speed;
	}
}