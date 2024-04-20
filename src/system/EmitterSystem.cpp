#include "EmitterSystem.h"

EmitterSystem::EmitterSystem(Scene& scene) : scene{scene} {}

void EmitterSystem::update() {
	for (EntityIndex i : view) {
		Emitter& emitter = scene.getComponent<Emitter>(i);

		if (emitter.particlesPerSecond == 0.0f) continue;

		// check if emitter should spawn particles
		const float secondsBetweenParticles = 1.0f / emitter.particlesPerSecond;
		emitter.intervalTimerSeconds += ofGetLastFrameTime();
		if (emitter.intervalTimerSeconds < secondsBetweenParticles) continue;

		// calculate how many new particles to create
		uint numParticles =
			emitter.intervalTimerSeconds / secondsBetweenParticles;

		// reset interval
		emitter.intervalTimerSeconds = 0.0f;

		// create particles and invoke spawn callback
		for (size_t particleCount = 0; particleCount < numParticles;
			 particleCount++) {
			// create entity
			EntityIndex entityIndex = scene.addEntity();
			// assign a COPY of the emitter's transform
			scene.assignComponent<Transform>(
				entityIndex, Transform{scene.getComponent<Transform>(i)});
			// invoke onSpawn
			emitter.onSpawn(entityIndex);
		}
	}
}