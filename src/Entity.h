#include <bitset>

const int maxComponents{32};

struct Entity {
	unsigned int ID;
	std::bitset<maxComponents> componentMask;
};
