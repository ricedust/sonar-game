#pragma once

#include <iostream>
#include <iterator>

#include "Component.h"

/// @brief A bitmask of component indices used to track what components are
/// registered to an entity.
using ComponentMask = std::bitset<maxComponents>;

/// @brief An entity stores only information about what components are
/// registered to it.
struct Entity {
	ComponentMask mask{};
};

/// @brief An iterator to used by an Entityview.
struct EntityIterator {
   private:
	EntityIndex index{0};
	const std::vector<Entity>& entities;
	const ComponentMask& mask{};
	const bool includeAllEntities{false};

   public:
	using iterator_category = std::input_iterator_tag;
	using difference_type = int;

	EntityIterator(EntityIndex index, const std::vector<Entity>& entities,
				   const ComponentMask& mask, bool includeAllEntities);

	EntityIndex operator*() const;
	EntityIterator& operator++();

	friend bool operator==(const EntityIterator& a, const EntityIterator& b);
	friend bool operator!=(const EntityIterator& a, const EntityIterator& b);
};

/// @brief A view to iterate over only entities with specific components.
/// @tparam ...ComponentTypes The component types to filter entities by.
template <typename... ComponentTypes>
class EntityView {
   private:
	const std::vector<Entity>& entities;
	ComponentMask mask{};
	bool includeAllEntities{false};

   public:
	EntityView(const std::vector<Entity>& entities);
	const EntityIterator begin() const;
	const EntityIterator end() const;
};

template <typename... ComponentTypes>
EntityView<ComponentTypes...>::EntityView(const std::vector<Entity>& entities)
	: entities{entities} {
	// if no component types provided, do not filter entities
	if (sizeof...(ComponentTypes) == 0) {
		mask.set();
		includeAllEntities = true;
		return;
	}

	// else, construct mask based on component types
	ComponentIndex componentIndices[] = {
		getComponentIndex<ComponentTypes>()...};
	for (size_t i = 0; i < sizeof...(ComponentTypes); i++) {
		mask.set(componentIndices[i]);
	}
};

template <typename... ComponentTypes>
const EntityIterator EntityView<ComponentTypes...>::begin() const {
	EntityIndex firstIndex = 0;
	while (!includeAllEntities && firstIndex < entities.size() &&
		   mask != (mask & entities[firstIndex].mask)) {
		firstIndex++;
	}
	return EntityIterator{firstIndex, entities, mask, includeAllEntities};
}

template <typename... ComponentTypes>
const EntityIterator EntityView<ComponentTypes...>::end() const {
	return EntityIterator{entities.size(), entities, mask, includeAllEntities};
}