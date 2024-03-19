#include "Scene.h"

EntityID Scene::addEntity() {
	entities.push_back({entities.size()});
	return entities.back().id;
}
