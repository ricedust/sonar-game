#pragma once

#include "Scene.h"

class Player : public SceneObject {
	int nEnergy{0};
	void update();
	void draw();

   public:
	Player() = default;
	Player(int initialEnergy);
};
