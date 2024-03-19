#pragma once

#include <bitset>

const int maxComponents{32};
typedef std::bitset<maxComponents> ComponentMask;
typedef unsigned long EntityID;

struct Entity {
	EntityID id{};
	ComponentMask componentMask{};
};
