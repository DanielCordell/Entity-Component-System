#include "Includes/component.h"

namespace ecs {

	Component::Component(ComponentType type) : type(type) { }

	enum Component::ComponentType {
		NUM_TYPES
	};
}