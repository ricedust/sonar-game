#pragma once

#include "Collider.h"
#include "Scene.h"
#include "Transform.h"
#include "ofMain.h"

class CollisionSystem {
	Scene& scene;
	EntityView<Collider> view{scene.getEntities()};

   public:
	CollisionSystem(Scene& scene);
	bool isOverlapping(EntityIndex a, EntityIndex b) const;
	void drawDebug() const;
};
