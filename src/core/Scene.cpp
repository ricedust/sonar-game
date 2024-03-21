#include "Scene.h"

EntityIndex Scene::addEntity() {
	// check if an index can be reused
	if (!freeIndices.empty()) {
		EntityIndex reclaimedIndex = freeIndices.back();
		freeIndices.pop_back();
		return reclaimedIndex;
	}

	// otherwise create a new row
	entities.emplace_back(entities.size());
	return entities.back().index;
}

void Scene::destroyEntity(EntityIndex entityIndex) {
	entities[entityIndex].mask.reset();
	freeIndices.push_back(entityIndex);
}