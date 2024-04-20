#include "ControlSystem.h"

ControlSystem::ControlSystem(Scene& scene, const InputSystem& inputSystem)
	: scene{scene}, inputSystem{inputSystem} {}

void ControlSystem::update(EntityIndex playerIndex,
						   EntityIndex bulletEmitterIndex) {
	// get components
	Player& player = scene.getComponent<Player>(playerIndex);
	Rigidbody& rigidbody = scene.getComponent<Rigidbody>(playerIndex);
	Transform& transform = scene.getComponent<Transform>(playerIndex);

	glm::vec3 forwardForce{0, inputSystem.getForward() * player.forceMagnitude,
						   0};

	// let world force be the rotated forward force (according to heading)
	glm::vec3 worldForce =
		glm::rotateZ(forwardForce, glm::radians(transform.rotationDegrees));

	// calculate torque
	float torque{-inputSystem.getTurn() * player.torqueMagnitude};

	// add force and torque to rigidbody
	rigidbody.forces.emplace(worldForce);
	rigidbody.torques.emplace(torque);

	if (!inputSystem.isFiring())
		scene.getComponent<Emitter>(bulletEmitterIndex).particlesPerSecond = 0;
}