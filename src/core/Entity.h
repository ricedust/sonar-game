#pragma once

#include <bitset>

#include "Constraints.h"

using ComponentMask = std::bitset<maxComponents>;
using EntityIndex = ulong;

struct Entity {
	EntityIndex index{};
	ComponentMask mask{};
};
