#include "SceneObject.h"

SceneObject::SceneObject(Transform transform) : transform{transform} {}

SceneObject::SceneObject(Transform transform, Collider collider)
	: transform{transform}, collider{collider} {}

Transform SceneObject::getTransform() const { return transform; }
Collider SceneObject::getCollider() const { return collider; }

void drawDebug(const SceneObject &sceneObject) {
	auto transform = sceneObject.getTransform();
	auto collider = sceneObject.getCollider();

	ofPushStyle();
	ofSetColor(ofColor::white);

	ofDrawCircle(transform.position, collider.radius);

	ofPopStyle();
}

bool isOverlapping(const SceneObject &a, const SceneObject &b) {
	// only circles supported currently
	if (a.getCollider().type != ColliderType::circle ||
		b.getCollider().type != ColliderType::circle)
		return false;

	auto distance =
		glm::distance(a.getTransform().position, b.getTransform().position);
	auto radiusSum = a.getCollider().radius + b.getCollider().radius;
	return distance < radiusSum;
}
