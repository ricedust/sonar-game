#pragma once

#include <vector>
#include <memory>

class SceneObject {
   public:
	virtual void update() = 0;
	virtual void draw() = 0;
};

class Scene {
	std::vector<std::unique_ptr<SceneObject>> sceneList;
};
