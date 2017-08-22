#pragma once

#include <bitset>
#include <memory>
#include <vector>

#include "constants.h"
#include "component.h"
#include "logger.h"

namespace ecs {
	// An Entity is a grouping of components. An entity can only have one of each component type.
	class Entity {
	private:
		std::vector<std::shared_ptr<Component>> components;
		std::bitset<static_cast<size_t>(consts::ComponentType::NUM_TYPES)> compflags;
		int ID;
	public:
		//Testing to see if an entity contains a specific Component
		template <class T> bool has();
		template <class T1, class T2, class... Other> bool has();

		//Removing Components
		template <class T> void remove();
		void clear();

		//Component Manipulation
		template <class T> void add();
		template <class T> std::shared_ptr<Component> get();

		~Entity();
	};
	template<class T>
	bool Entity::has() {
		if (!isComponent<T>()) {
			Logger::Log(Logger::ERROR, "Trying to detect a component that is not a component type. Will ignore.");
			return false;
		}
		if (compflags.test(T::type)) return true;
		return false;
	}

	template <class T1, class T2, class ... Other>
	bool Entity::has() {
		return has<T1>() && has<T2, Other ...>();
	}
	template<class T>
	void Entity::remove() {
		if (!isComponent<T>()) {
			Logger::Log(Logger::WARNING, "Trying to remove a component that is not a component type. Will ignore.");
			return;
		}
		for (auto i = components.begin(); i != components.end(); ++i) {
			if ((*i)->type == T::type) {
				compflags.set(T::type, false);
				components.erase(i);
			}
		}
	}
	template<class T>
	void Entity::add() {

	}
	template<class T>
	std::shared_ptr<Component> Entity::get()
	{
		if (!isComponent<T>()) {
			Logger::Log(Logger::ERROR, "Trying to get a component that is not a component type!");
			return nullptr;
		}
		for (auto i = components.begin(); i != components.end(); ++i) {
			if ((*i)->type == T::type) return *i;
		}
		Logger::Log(Logger::ERROR, "Cannot find component in entity of ID" + std::to_string(ID) + "!");
		return nullptr;
	}
}
