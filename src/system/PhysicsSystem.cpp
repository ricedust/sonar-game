#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(Scene& scene) : scene{scene} {}

void PhysicsSystem::update() {
	for (EntityIndex i : view) {
		Rigidbody& rigidbody = scene.getComponent<Rigidbody>(i);
		Transform& transform = scene.getComponent<Transform>(i);

		glm::vec3 netForce{};
		float netTorque{};

		// flatten the forces and torques into netForce and netTorque
		while (!rigidbody.forces.empty()) {
			netForce += rigidbody.forces.front();
			rigidbody.forces.pop();
		}
		while (!rigidbody.torques.empty()) {
			netTorque += rigidbody.torques.front();
			rigidbody.torques.pop();
		}

		float deltaTime = ofGetLastFrameTime();

		// assign accelerations
		rigidbody.acceleration = netForce;
		rigidbody.angularAcceleration = netTorque;

		// update position
		transform.position += rigidbody.velocity * deltaTime;
		rigidbody.velocity += rigidbody.acceleration * deltaTime;
		rigidbody.velocity *= std::pow(rigidbody.speedDamping, deltaTime);

		// update rotation
		transform.rotationDegrees +=
			glm::degrees(rigidbody.angularVelocity) * deltaTime;
		rigidbody.angularVelocity += rigidbody.angularAcceleration * deltaTime;
		rigidbody.angularVelocity *= std::pow(rigidbody.rotationDamping, deltaTime);
	}
}