#include "FadeSystem.h"

FadeSystem::FadeSystem(Scene &scene) : scene{scene} {}

void FadeSystem::update() {
	for (EntityIndex i : view) {
		Renderer &renderer{scene.getComponent<Renderer>(i)};
		Fader &fader{scene.getComponent<Fader>(i)};

		renderer.alpha = std::clamp(
			(int)(renderer.alpha - fader.fadeRate * ofGetLastFrameTime()), 0,
			255);
	}
}