#pragma once

#include "Emitter.h"
#include "Lifespan.h"
#include "Rigidbody.h"
#include "Scene.h"
#include "Transform.h"

class EmitterSystem {
   private:
	Scene &scene;
	EntityView<Emitter, Transform> view{scene.getEntities()};

   public:
	EmitterSystem(Scene &scene);
	void update();
};