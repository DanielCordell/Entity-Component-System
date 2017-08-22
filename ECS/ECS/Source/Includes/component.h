#pragma once
#include <type_traits>

namespace ecs {

	class Component {
	public:
		enum ComponentType;

		static const ComponentType type;
		Component();
	};

	template<class T>
	bool isComponent()
	{
		return std::is_base_of<Component, T>::value;
	}
}
