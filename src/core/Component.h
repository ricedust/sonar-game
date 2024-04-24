#pragma once

#include <stddef.h>

#include <bitset>
#include <cstddef>
#include <memory>
#include <vector>

#include "Constraints.h"

/// @brief Where an entity is indexed in the scene and component pools.
using EntityIndex = size_t;
/// @brief The unique index assigned to each component type.
using ComponentIndex = size_t;

extern ComponentIndex componentTypeCounter;

/// @brief Generates or recalls the index of a given component.
/// @tparam T The component type.
/// @return A component index.
template <typename T>
ComponentIndex getComponentIndex() {
	static ComponentIndex componentIndex = componentTypeCounter++;
	return componentIndex;
};

/// @brief A memory pool that gets inititialized at runtime to be the
/// size of the component * max # entities.
struct ComponentPool {
   private:
	size_t componentSize{0};
	std::unique_ptr<std::byte[]> bytes{nullptr};

   public:
	ComponentPool() = default;
	ComponentPool(size_t componentSize);

	/// @tparam T The component type.
	/// @param entityIndex The entity's index.
	/// @return A reference to the component.
	template <typename T>
	T& get(EntityIndex entityIndex);

	size_t getComponentSize();
};

template <typename T>
T& ComponentPool::get(EntityIndex entityIndex) {
	T* component =
		reinterpret_cast<T*>(bytes.get() + entityIndex * componentSize);
	return *component;
}