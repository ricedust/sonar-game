#include "Scene.h"

EntityIndex Scene::addEntity() {
	// check if an index can be reused
	if (!freeIndices.empty()) {
		EntityIndex reclaimedIndex = freeIndices.front();
		freeIndices.pop();
		return reclaimedIndex;
	}

	// otherwise create a new row
	entities.emplace_back();
	return entities.size() - 1;
}

const std::vector<Entity>& Scene::getEntities() const { return entities; }

void Scene::destroyEntity(EntityIndex entityIndex) {
	entities[entityIndex].mask.reset();
	freeIndices.emplace(entityIndex);
}

void Scene::reset() {
	entities.clear();
	freeIndices = {};
}