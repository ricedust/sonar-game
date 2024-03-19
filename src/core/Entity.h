#pragma once

#include <bitset>

#include "Limits.h"

typedef std::bitset<maxComponents> ComponentMask;
typedef ulong EntityID;

struct Entity {
	EntityID id{};
	ComponentMask componentMask{};
};
