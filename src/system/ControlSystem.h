#pragma once

#include "Emitter.h"
#include "InputSystem.h"
#include "Player.h"
#include "Rigidbody.h"
#include "Scene.h"
#include "Transform.h"
#include "ofMain.h"

class ControlSystem {
	Scene& scene;
	const InputSystem& inputSystem;

   public:
	ControlSystem(Scene& scene, const InputSystem& inputSystem);
	void update(EntityIndex playerIndex, EntityIndex bulletEmitterIndex);
};