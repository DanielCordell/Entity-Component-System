#pragma once
#include <type_traits>


namespace ecs {

	class Component {
	public:
		enum ComponentType;

		static const ComponentType type;
	};

	template<class C>
	bool isComp()
	{
		return std::is_base_of<Component, C>::value;
	}
}
