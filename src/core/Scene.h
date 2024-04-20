#pragma once

#include <assert.h>

#include <iostream>
#include <vector>
#include <queue>

#include "Component.h"
#include "Entity.h"

/// @brief A Scene is a table that maps components to entities. An entity
/// can be thought of as a row, and component pools as columns
class Scene {
	std::vector<Entity> entities{};
	std::queue<EntityIndex> freeIndices{};
	std::vector<ComponentPool> componentPools{};

   public:
	/// @brief Adds an entity to the scene.
	/// @return The new entity's index.
	EntityIndex addEntity();

	/// @return A reference to the vector of entities.
	const std::vector<Entity>& getEntities() const;

	/// @brief Unregisters the entity from all components. The entityIndex may
	/// be reclaimed by a new entity.
	/// @param entityIndex The entity's index to relinquish.
	void destroyEntity(EntityIndex entityIndex);

	/// @brief Clears all entities.
	void reset();

	/// @brief Retreives a component belonging to an entity.
	/// @tparam T The component type.
	/// @param entityIndex The entity's index.
	/// @return A component reference.
	template <typename T>
	T& getComponent(EntityIndex entityIndex);

	/// @brief Moves and assigns a component to an entity.
	/// @tparam T The component type.
	/// @param entityIndex The entity's index.
	/// @param component A sink for the component to assign.
	template <typename T>
	void assignComponent(EntityIndex entityIndex, T&& component);

	/// @brief Assigns a component to an entity.
	/// @tparam T The component type.
	/// @param entityIndex The entity's index.
	template <typename T>
	void assignComponent(EntityIndex entityIndex);

	/// @brief Removes a component from an entity.
	/// @tparam T The component type.
	/// @param entityIndex The entity's index.
	template <typename T>
	void removeComponent(EntityIndex entityIndex);
};

template <typename T>
T& Scene::getComponent(EntityIndex entityIndex) {
	ComponentIndex componentIndex = getComponentIndex<T>();

	// assert(entities[entityIndex].mask.test(componentIndex) && "Entity missing
	// component.");
	if (!entities[entityIndex].mask.test(componentIndex))
		std::cout << "MISSING COMPONENT" << '\n';

	return componentPools[componentIndex].get<T>(entityIndex);
}

template <typename T>
void Scene::assignComponent(EntityIndex entityIndex, T&& component) {
	ComponentIndex componentIndex = getComponentIndex<T>();

	// allocate room for new pool if needed
	if (componentIndex >= componentPools.size())
		componentPools.resize(componentIndex + 1);

	// initialize pool if it doesn't exist
	if (componentPools[componentIndex].getComponentSize() == 0)
		componentPools[componentIndex] = {sizeof(T)};

	// move the component into the pool at the entityIndex
	componentPools[componentIndex].get<T>(entityIndex) = std::move(component);

	// set the entities component mask
	entities[entityIndex].mask.set(componentIndex);
}

template <typename T>
void Scene::assignComponent(EntityIndex entityIndex) {
	assignComponent<T>(entityIndex, {});
}

template <typename T>
void Scene::removeComponent(EntityIndex entityIndex) {
	ComponentIndex componentIndex = getComponentIndex<T>();
	entities[entityIndex].mask.reset(componentIndex);
}