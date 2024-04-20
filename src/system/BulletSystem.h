#pragma once

#include "Bullet.h"
#include "Rigidbody.h"
#include "Scene.h"
#include "Transform.h"

class BulletSystem {
	Scene &scene;
	EntityView<Bullet, Rigidbody, Transform> view{scene.getEntities()};

   public:
	BulletSystem(Scene &scene);
	void update();
};