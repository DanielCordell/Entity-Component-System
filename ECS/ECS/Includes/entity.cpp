#include <algorithm>

#include "entity.h"

namespace ecs{
	Component* Entity::add(Component newComp)
	{
		// Can't add a new component when one of that type already exists.
		if (has(newComp.type)) return {};
		components.push_back(std::make_unique<Component>(newComp));
		return components.back().get();
	}

	Component* Entity::get(Component::ComponentType type)
	{
		// Can't get a component if one of that type does not exist.
		if (!has(type)) return {};
		for (uint32_t i = 0; i < components.size(); ++i) {
			auto& component = components[i];
			if (component->type == type) return component.get();
		}
		return {};
	}

	bool Entity::has(Component::ComponentType type)
	{
		//Checks to see if the entity has a component of a specific type.
		auto found = std::find_if(components.begin(), components.end(), [type](std::unique_ptr<Component>& component)
		{
			return type == component->type;
		});
		return found != components.end();
	}

}
