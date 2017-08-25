#pragma once
#include <memory>
#include <vector>

#include "entity.h"

namespace ecs {
	class EntityManager {
	public:
		typedef std::shared_ptr<Entity> entityPtr;
		typedef std::vector<entityPtr> entityList;

		EntityManager();

		//Getting Entities based on ID
		entityPtr getEntityByID(const Entity::idType id) const;

		//Getting Entities based on their Components
		template <class C> 
		entityList getEntitiesByComp() const;
		template <class C1, class C2, class... More> 
		entityList getEntitiesByComp() const;

		//Adding Entities
		entityPtr createEntity();
		entityPtr addEntity(const Entity& entity);

		//Removing Entities
		void removeEntity(const Entity::idType id);
		void clear();

		~EntityManager();
	private:
		Entity::idType eidCount;
		entityList entities;
	};

	template <class C>
	EntityManager::entityList EntityManager::getEntitiesByComp() const {
		entityList list;
		for (auto i = entities.begin(); i != entities.end(); ++i) {
			if ((*i)->hasComp<C>()) list.push_back(*i);
		}
		return list;
	}

	template <class C1, class C2, class ... More>
	EntityManager::entityList EntityManager::getEntitiesByComp() const {
		entityList list;
		for (auto i = entities.begin(); i != entities.end(); ++i) {
			if ((*i)->hasComp<C1, C2, More ...>()) list.push_back(*i);
		}
		return list;
	}
}
