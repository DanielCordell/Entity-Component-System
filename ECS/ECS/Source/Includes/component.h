#pragma once
#include <type_traits>

#include "constants.h"


namespace ecs {

	class Component {
	public:
		static const consts::ComponentType type;
	};

	template<class C>
	bool isComp() {
		return std::is_base_of<Component, C>::value;
	}

}
