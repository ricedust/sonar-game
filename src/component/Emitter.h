#pragma once

#include <functional>

#include "Scene.h"
#include "ofMain.h"

enum class EmitterType { explosion, enemy, bullet };

struct Emitter {
	int particlesPerSecond{};
	/// @brief A callback for each time an entity is spawned by the emitter.
	std::function<void(EntityIndex entityIndex)> onSpawn{};
	float intervalTimerSeconds{};
};
