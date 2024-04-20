#pragma once

#include <sys/types.h>

/// @brief Attributes of the player.
struct Player {
	int nEnergy{};
	int remainingEnergy{};
	float forceMagnitude{};
	float torqueMagnitude{};
};
