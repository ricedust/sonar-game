#pragma once

#include <bitset>

#include "Constraints.h"

typedef std::bitset<maxComponents> ComponentMask;
typedef ulong EntityIndex;

struct Entity {
	EntityIndex index{};
	ComponentMask componentMask{};
};
