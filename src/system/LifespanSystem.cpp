#include "LifespanSystem.h"

LifespanSystem::LifespanSystem(Scene &scene) : scene{scene} {}

void LifespanSystem::update() {
	for (EntityIndex i : view) {
		Lifespan &lifespan = scene.getComponent<Lifespan>(i);

		// update age
		lifespan.ageSeconds += ofGetLastFrameTime();

		// destroy entity if age exceeds limit
		if (lifespan.ageSeconds > lifespan.limitSeconds) scene.destroyEntity(i);
	}
}