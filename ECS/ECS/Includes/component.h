#pragma once

namespace ecs {

	class Component {
	public:
		enum ComponentType;

		const ComponentType type;
		Component(ComponentType type);
	};

}