#pragma once

#include <assert.h>

#include <vector>

#include "Component.h"
#include "Entity.h"

/// @brief A Scene is a table that maps entities to components. An entity
/// can be thought of as a row, and component pools as columns
class Scene {
	std::vector<Entity> entities{};
	std::vector<EntityIndex> freeIndices{};
	std::vector<ComponentPool> componentPools{};

   public:
	/// @brief Adds an entity to the scene.
	/// @return The new entity's index.
	EntityIndex addEntity();

	/// @brief Unregisters the entity from all components. The entityIndex may
	/// be reclaimed by a new entity.
	/// @param entityIndex The entity's index to relinquish.
	void destroyEntity(EntityIndex entityIndex);

	/// @brief Attempts to get component belonging to an entity.
	/// @tparam T The component type.
	/// @param entityIndex The entity's index.
	/// @param outComponent An out reference to the component.
	/// @return Whether or not the entity has the component.
	template <typename T>
	bool tryGetComponent(EntityIndex entityIndex, T& outComponent) {
		ComponentIndex componentIndex = getComponentIndex<T>();

		if (!entities[entityIndex].componentMask.test(componentIndex))
			return false;

		outComponent = componentPools[componentIndex].get<T>(entityIndex);

		return true;
	}

	/// @brief Assigns a component to an entity.
	/// @tparam T The component type.
	/// @param entityIndex The entity's index.
	/// @param component A sink for the component to assign.
	template <typename T>
	void assignComponent(EntityIndex entityIndex, T&& component) {
		ComponentIndex componentIndex = getComponentIndex<T>();

		// allocate room for new pool if needed
		if (componentIndex >= componentPools.size())
			componentPools.resize(componentIndex + 1);

		// initialize pool if it doesn't exist
		if (componentPools[componentIndex].componentSize == 0)
			componentPools[componentIndex] = {sizeof(T)};

		// move the component into the pool at the entityIndex
		componentPools[componentIndex].get<T>(entityIndex) =
			std::move(component);

		// set the entities component mask
		entities[entityIndex].componentMask.set(componentIndex);
	}

	/// @brief Removes a component from an entity.
	/// @tparam T The component type.
	/// @param entityIndex The entity's index.
	template <typename T>
	void removeComponent(EntityIndex entityIndex) {
		ComponentIndex componentIndex = getComponentIndex<T>();
		entities[entityIndex].componentMask.reset(componentIndex);
	}
};
