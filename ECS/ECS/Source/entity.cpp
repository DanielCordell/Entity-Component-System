#include "Includes/entity.h"

namespace ecs{
	void Entity::clear(){
		components.clear();
	}
	Entity::~Entity() {
		clear();
	}
}
