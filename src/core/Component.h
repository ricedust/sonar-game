#pragma once

#include <stddef.h>

#include <cstddef>
#include <memory>
#include <vector>

#include "Constraints.h"
#include "Entity.h"

using ComponentIndex = uint;

extern ComponentIndex componentTypeCounter;

/// @brief Generates or recalls the index of a given component.
/// @tparam T The component type.
/// @return a component index.
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
};

template <typename T>
T& ComponentPool::get(EntityIndex entityIndex) {
	T* component =
		reinterpret_cast<T*>(bytes.get() + entityIndex * componentSize);
	return *component;
}