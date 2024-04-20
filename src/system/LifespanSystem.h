#pragma once

#include "Lifespan.h"
#include "Scene.h"
#include "ofMain.h"

class LifespanSystem {
   private:
	Scene& scene;
	EntityView<Lifespan> view{scene.getEntities()};

   public:
	LifespanSystem(Scene& scene);
	void update();
};
