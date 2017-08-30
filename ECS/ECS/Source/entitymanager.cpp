#include "Includes/entitymanager.h"
#include "Includes/logger.h"

namespace ecs {

	EntityManager::EntityManager() : eidCount(0) {}

	EntityManager::entityPtr EntityManager::getEntityByID(const Entity::idType id) const {
		for (auto i = entities.begin(); i != entities.end(); ++i) {
			if ((*i)->id == id) return *i;
		}
		Logger::Log(Logger::ERROR, "Trying to get Entity of ID " + std::to_string(id) + " which does not exist!");
		return nullptr;
	}

	EntityManager::entityPtr EntityManager::createEntity()
	{
		return addEntity(Entity(++eidCount));
	}

	EntityManager::entityPtr EntityManager::addEntity(const Entity& entity)
	{
		entities.push_back(std::make_shared<Entity>(entity));
		return entities.back();
	}

	void EntityManager::removeEntity(const Entity::idType id) {
		for (auto i = entities.begin(); i != entities.end(); ++i) {
			if ((*i)->id == id) entities.erase(i);
		}

	}

	void EntityManager::clear() {
		entities.clear();
	}

	EntityManager::~EntityManager(){
		clear();
	}

}