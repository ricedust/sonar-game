#pragma once

#include <bitset>

#include "Constraints.h"

typedef std::bitset<maxComponents> ComponentMask;
typedef ulong EntityID;

struct Entity {
	EntityID id{};
	ComponentMask componentMask{};
};
