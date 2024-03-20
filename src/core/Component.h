#pragma once

#include <stddef.h>

#include <cstddef>
#include <memory>
#include <vector>

#include "Constraints.h"

typedef uint ComponentID;

extern ComponentID componentTypeCounter;

/// @brief Generates or recalls the ID of a given component.
/// @tparam T The component type.
/// @return a component ID.
template <typename T>
ComponentID getID() {
	static ComponentID componentID = componentTypeCounter++;
	return componentID;
};

/// @brief Basically a memory pool that gets inititialized at runtime to be the
/// size of the component * max # entities.
struct ComponentPool {
   private:
	size_t componentSize{0};
	std::unique_ptr<std::byte[]> bytes{nullptr};

   public:
	ComponentPool(size_t componentSize);

	/// @tparam T The component type.
	/// @param index The index of the component.
	/// @return A reference to the component.
	template <typename T>
	T& get(size_t index) {
		T* component = static_cast<T*>(bytes.get() + index * componentSize);
		return *component;
	}
};