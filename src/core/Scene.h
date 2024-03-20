#pragma once

#include <vector>

#include "Component.h"
#include "Entity.h"

class Scene {
	std::vector<Entity> entities{};
	std::vector<ComponentPool> componentPools{};

   public:
	EntityID addEntity();

	template <typename T>
	void addComponent(EntityID entityID, T &component) {
		ComponentID componentID = getID<T>();

		// create another pool if new component
		if (componentID >= componentPools.size()) {
			componentPools.resize(componentID + 1);
		}
		

		entities[id].componentMask.set(componentID);
	}
};
