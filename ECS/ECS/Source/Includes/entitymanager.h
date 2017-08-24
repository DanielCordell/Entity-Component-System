#pragma once
#include <cstdint>
#include <memory>
#include <vector>

#include "entity.h"

namespace ecs {
	class EntityManager {
	public:
		typedef std::shared_ptr<Entity> entityPtr;
		typedef std::vector<entityPtr> entityList;

		entityList getEntitiesByID();
		template <class C> 
		entityList getEntitiesByComp();
		template <class C1, class C2, class... More> 
		entityList getEntityByComp();

		entityPtr createEntity();
		entityPtr addEntity(Entity entity);
	private:
		static uint64_t eCount;
		static entityList entities;
	};
}
