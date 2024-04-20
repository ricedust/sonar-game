#pragma once

#include "Fader.h"
#include "Renderer.h"
#include "Scene.h"

class FadeSystem {
	Scene &scene;
	EntityView<Fader, Renderer> view{scene.getEntities()};

   public:
	FadeSystem(Scene &scene);
	void update();
};