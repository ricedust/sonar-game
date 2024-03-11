#pragma once

#include <memory>
#include <vector>

#include "Agent.h"
#include "SceneObject.h"

class AgentEmitter : public SceneObject {
	vector<unique_ptr<Agent>> agents{};
	shared_ptr<SceneObject> target;

	float timeSinceLastSpawnSeconds{0};
	int collidedAgentsCount{0};

   public:
	int nAgents{0};
	float agentLifespan{0};
	float agentSpawnInterval{0.5};
	float agentSpeed{0};
	float agentRotationSpeed{0};

	AgentEmitter() = default;
	AgentEmitter(shared_ptr<SceneObject> target);

	void update();
	void draw();

	int getCollidedAgentsCount() const;
	void setTarget(shared_ptr<SceneObject> target);
};
