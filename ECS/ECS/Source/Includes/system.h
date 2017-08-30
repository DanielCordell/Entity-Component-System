#pragma once
#include "entitymanager.h"

namespace ecs {
	class System {
	// A System uses components to interact with one another.
	public:
		System(EntityManager& e) : entityManager(e){}
	private:
		EntityManager& entityManager;
	};
}
