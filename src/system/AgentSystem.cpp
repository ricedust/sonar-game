#include "AgentSystem.h"

AgentSystem::AgentSystem(Scene &scene, const CollisionSystem &collisionSystem)
	: scene{scene}, collisionSystem{collisionSystem} {}

void AgentSystem::update(EntityIndex playerIndex) {
	for (EntityIndex i : agentView) {
		updateAgentForce(i,
						 scene.getComponent<Transform>(playerIndex).position);
		checkBulletCollision(i);
	}

	// refresh agent view in new loop
	for (EntityIndex i : agentView) {
		checkPlayerCollision(i, playerIndex);
	}
}

void AgentSystem::updateAgentForce(EntityIndex i,
								   const glm::vec3 &targetPosition) {
	// fetch components
	Agent &agent = scene.getComponent<Agent>(i);
	Rigidbody &rigidbody = scene.getComponent<Rigidbody>(i);
	Transform &transform = scene.getComponent<Transform>(i);

	// find difference between where the agent is pointed and where it needs
	// to point
	auto targetHeading = glm::normalize(targetPosition - transform.position);
	auto currentHeading = glm::rotateZ(glm::vec3{0, 1, 0},
									   glm::radians(transform.rotationDegrees));
	auto errorAngle =
		glm::orientedAngle(currentHeading, targetHeading, glm::vec3{0, 0, 1});

	// apply torque to correct towards target heading
	if (errorAngle > 0) {
		rigidbody.torques.emplace(agent.torqueMagnitude);
	} else
		rigidbody.torques.emplace(-agent.torqueMagnitude);

	// continue pushing agent in current heading
	glm::vec3 worldForce =
		glm::rotateZ(glm::vec3{0, agent.forceMagnitude, 0},
					 glm::radians(transform.rotationDegrees));
	rigidbody.forces.emplace(worldForce);
}

void AgentSystem::checkBulletCollision(EntityIndex agentIndex) {
	// loop over every bullet and check for collision with agent
	for (EntityIndex bulletIndex : bulletView) {
		if (collisionSystem.isOverlapping(agentIndex, bulletIndex)) {
			createExplosion(scene.getComponent<Transform>(agentIndex).position);
			// destroy bullet and agent
			scene.destroyEntity(agentIndex);
			scene.destroyEntity(bulletIndex);
			return;
		}
	}
}

void AgentSystem::checkPlayerCollision(EntityIndex agentIndex,
									   EntityIndex playerIndex) {
	if (collisionSystem.isOverlapping(agentIndex, playerIndex)) {
		// invoke callback and destroy agent
		onPlayerCollision();
		createExplosion(scene.getComponent<Transform>(agentIndex).position);
		scene.destroyEntity(agentIndex);
	}
}

void AgentSystem::createExplosion(const glm::vec3 &origin) {
	EntityIndex explosionIndex = scene.addEntity();

	// make explosion happen at origin
	scene.assignComponent<Transform>(explosionIndex, {origin, 0, glm::vec3{1}});
	// make emitter temporary
	scene.assignComponent<Lifespan>(explosionIndex, {0.25f});

	// configure emitter to spawn explosion particles
	Emitter emitter{};
	emitter.particlesPerSecond = 32;
	emitter.onSpawn = [&](EntityIndex i) {
		// apply random force
		Rigidbody rigidbody{};
		rigidbody.forces.emplace(glm::rotateZ(
			glm::vec3{ofRandom(30000.0f), 0, 0}, ofRandom(TWO_PI)));
		scene.assignComponent<Rigidbody>(i, std::move(rigidbody));

		// random particle size
		scene.getComponent<Transform>(i).scale *= ofRandom(0.1f, 0.4f);

		scene.assignComponent<Lifespan>(i);
		scene.assignComponent<Renderer>(i, {Sprite::dot, {32, 32, 0}});
		scene.assignComponent<Fader>(i, {255});
	};
	scene.assignComponent<Emitter>(explosionIndex, std::move(emitter));

	AudioSystem::play(Sound::explosion);
}
