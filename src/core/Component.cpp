#include "Component.h"
ComponentID componentTypeCounter{0};

ComponentPool::ComponentPool(size_t componentSize)
	: componentSize{componentSize},
	  bytes{std::make_unique<std::byte[]>(componentSize * maxEntities)} {}