#pragma once

#include <vector>

#include "Component.h"
#include "Entity.h"

class Scene {
	std::vector<Entity> entities{};

   public:
	EntityID addEntity();

	template <typename T>
	void addComponentToEntity(EntityID id) {
		int componentID = getID<T>();



		entities[id].componentMask.set(componentID);
	}
};
