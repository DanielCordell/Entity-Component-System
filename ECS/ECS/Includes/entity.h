#pragma once

#include <vector>
#include <memory>

#include "component.h"

namespace ecs {
	// An Entity is a grouping of components. An entity can only have one of each component type.
	class Entity {
	private:
		std::vector<std::unique_ptr<Component>> components;

	public:
		//Gets a component from an entity based on its type;
		Component*	add(Component component);
		Component*	get(Component::ComponentType type);
		bool		has(Component::ComponentType type);
	};
}