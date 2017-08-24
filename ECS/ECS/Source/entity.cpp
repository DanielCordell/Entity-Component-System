#include "Includes/entity.h"

namespace ecs{
	void Entity::clear(){
		components.clear();
	}

	Entity::compPtr Entity::addComp(const Component& component) {
		components.push_back(std::make_shared<Component>(component));
		return components.back();
	}

	Entity::~Entity() {
		clear();
	}

}
