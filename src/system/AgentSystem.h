#pragma once

#include "Agent.h"
#include "AudioSystem.h"
#include "Bullet.h"
#include "CollisionSystem.h"
#include "Emitter.h"
#include "Fader.h"
#include "Lifespan.h"
#include "Player.h"
#include "Renderer.h"
#include "Rigidbody.h"
#include "Scene.h"
#include "Transform.h"
#include "ofMain.h"

class AgentSystem {
	Scene& scene;

	EntityView<Agent, Rigidbody, Transform, Collider> agentView{
		scene.getEntities()};

	EntityView<Bullet, Transform, Collider> bulletView{scene.getEntities()};

	const CollisionSystem& collisionSystem;

	void updateAgentForce(EntityIndex i, const glm::vec3& targetPosition);
	void checkBulletCollision(EntityIndex agentIndex);
	void checkPlayerCollision(EntityIndex agentIndex, EntityIndex playerIndex);
	void createExplosion(const glm::vec3& location);

   public:
	std::function<void()> onPlayerCollision{[]() {}};

	AgentSystem(Scene& scene, const CollisionSystem& collisionSystem);
	void update(EntityIndex playerIndex);
};