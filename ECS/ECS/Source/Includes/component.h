#pragma once
#include <type_traits>

#include "constants.h"


namespace ecs {

	class Component {
	public:
		static const consts::ComponentType type;
	};

	const consts::ComponentType Component::type = consts::ComponentType::EMPTY;

	template<class C>
	bool isComp()
	{
		return std::is_base_of<Component, C>::value;
	}

}
