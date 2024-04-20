#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(Scene& scene) : scene{scene} {}

bool CollisionSystem::isOverlapping(EntityIndex a, EntityIndex b) const {
	auto distance = glm::distance(scene.getComponent<Transform>(a).position,
								  scene.getComponent<Transform>(b).position);
	auto radiusSum = scene.getComponent<Collider>(a).circleRadius +
					 scene.getComponent<Collider>(b).circleRadius;
	return distance < radiusSum;
}

void CollisionSystem::drawDebug() const {
	ofPushStyle();
	ofSetColor(ofColor::white);

	for (EntityIndex i : view) {
		ofDrawCircle(scene.getComponent<Transform>(i).position,
					 scene.getComponent<Collider>(i).circleRadius);
	}
	ofPopStyle();
}