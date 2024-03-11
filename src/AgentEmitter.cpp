#include "AgentEmitter.h"

AgentEmitter::AgentEmitter(shared_ptr<SceneObject> target) : target{target} {};

void AgentEmitter::update() {
	// spawn next batch if past spawn interval
	timeSinceLastSpawnSeconds += ofGetLastFrameTime();

	if (timeSinceLastSpawnSeconds > agentSpawnInterval) {
		timeSinceLastSpawnSeconds = 0;

		for (int i = 0; i < nAgents; i++) {
			agents.push_back(make_unique<Agent>());
		}
	}

	// erase pointers to expired agents
	agents.erase(remove_if(agents.begin(), agents.end(),
						   [&](const unique_ptr<Agent> &agent) {
							   auto isExpired =
								   agent->getTimeAliveSeconds() > agentLifespan;
							   auto hasCollided =
								   isOverlapping(*agent, *target);
							   collidedAgentsCount += hasCollided;
							   return isExpired || hasCollided;
						   }),
				 agents.end());

	// update existing agents with slider values
	for (auto &agent : agents) {
		agent->speed = agentSpeed;
		agent->rotationSpeed = agentRotationSpeed;
		agent->setTargetPosition(target->getTransform().position);
		agent->update();
	}
}

void AgentEmitter::draw() {
	for (auto &agent : agents) {
		agent->draw();
		// drawDebug(*agent);
	}
}

int AgentEmitter::getCollidedAgentsCount() const { return collidedAgentsCount; }

void AgentEmitter::setTarget(shared_ptr<SceneObject> target) {
	this->target = move(target);
}