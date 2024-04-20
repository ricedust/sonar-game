#include "Entity.h"

EntityIterator::EntityIterator(EntityIndex index,
							   const std::vector<Entity>& entities,
							   const ComponentMask& mask,
							   bool includeAllEntities)
	: index{index},
	  entities{entities},
	  mask{mask},
	  includeAllEntities{includeAllEntities} {}

EntityIndex EntityIterator::operator*() const { return index; }

EntityIterator& EntityIterator::operator++() {
	do {
		index++;
		// 1. the index must be in bounds
		// 2. the component mask must be satisfied
	} while (!includeAllEntities && index < entities.size() &&
			 mask != (mask & entities[index].mask));
	return *this;
}

bool operator==(const EntityIterator& a, const EntityIterator& b) {
	return a.index == b.index || a.index == a.entities.size();
}

bool operator!=(const EntityIterator& a, const EntityIterator& b) {
	return a.index != b.index && a.index != a.entities.size();
}
