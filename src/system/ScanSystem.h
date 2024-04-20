#pragma once

#include "Agent.h"
#include "AudioSystem.h"
#include "Renderer.h"
#include "Scanner.h"
#include "Scene.h"
#include "Transform.h"
#include "ofMain.h"

class ScanSystem {
	Scene& scene;
	EntityView<Scanner, Transform> scannerView{scene.getEntities()};
	EntityView<Agent, Renderer, Transform> agentView{scene.getEntities()};

   public:
	ScanSystem(Scene& scene);
	void update(EntityIndex trueScannerIndex,
				const Transform& relativeTransform);
};