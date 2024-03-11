#pragma once

#include "Collider.h"
#include "Transform.h"
#include "ofMain.h"

/// @brief An object with a transform that can be updated and drawn.
class SceneObject {
   protected:
	Transform transform{};
	Collider collider{};

	SceneObject() = default;
	SceneObject(Transform transform);
	SceneObject(Transform transform, Collider collider);

   public:
	virtual void update() = 0;
	virtual void draw() = 0;

	Transform getTransform() const;
	Collider getCollider() const;
};

void drawDebug(const SceneObject &sceneObject);

bool isOverlapping(const SceneObject &a, const SceneObject &b);
