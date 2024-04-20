#pragma once

#include "Rigidbody.h"
#include "Scene.h"
#include "Transform.h"

class PhysicsSystem {
	Scene& scene;
	EntityView<Rigidbody, Transform> view{scene.getEntities()};

   public:
	PhysicsSystem(Scene& scene);
	void update();
};