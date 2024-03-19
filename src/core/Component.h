#pragma once

#include <stddef.h>

#include <cstddef>
#include <memory>
#include <vector>

#include "Limits.h"

extern int componentCounter;

/// @brief Generates or recalls the ID of a given component.
/// @tparam T The component type.
/// @return a component ID.
template <typename T>
int getID() {
	static int componentID = componentCounter++;
	return componentID;
};

/// @brief Basically a memory pool that gets inititialized at runtime to be the
/// size of the component * max entities.
struct ComponentPool {
   private:
	std::unique_ptr<std::byte[]> bytes{nullptr};
	size_t componentSize{0};

   public:
	ComponentPool(size_t componentSize);

	/// @tparam T The component type.
	/// @param index The index of the component.
	/// @return A reference to the component.
	template <typename T>
	T& get(size_t index) {
		T* component = static_cast<T*>(bytes + index * componentSize);
		return *component;
	}
};