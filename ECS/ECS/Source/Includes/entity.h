#pragma once

#include <bitset>
#include <memory>
#include <vector>
#include <any>

#include "constants.h"
#include "component.h"
#include "logger.h"

namespace ecs {
	// An Entity is a grouping of components. An entity can only have one of each component type.
	class Entity {
	public:
		typedef std::shared_ptr<Component> compPtr;
		typedef std::vector<compPtr> compList;
		typedef const uint64_t idType;

		//Testing to see if an entity contains a specific Component
		template <class C> bool hasComp();
		template <class C1, class C2, class... More> bool hasComp();

		//Removing Components
		template <class C> void removeComp();
		void clear();

		//Component Manipulation
		compPtr addComp(const Component& component);
		template <class C> compPtr addComp(std::initializer_list<std::any> args);
		template <class C> compPtr getComp();

		Entity(idType id) : id(id) {}

		~Entity();
	private:
		compList components;
		std::bitset<static_cast<size_t>(consts::ComponentType::NUM_TYPES)> compflags;
		idType id;
	};

	template<class C>
	bool Entity::hasComp() {
		if (!isComp<C>()) {
			Logger::Log(Logger::ERROR, "Trying to detect a component that is not a component type. Will ignore.");
			return false;
		}
		if (compflags.test(C::type)) return true;
		return false;
	}

	template <class C1, class C2, class ... More>
	bool Entity::hasComp() {
		return hasComp<C1>() && hasComp<C2, More ...>();
	}

	template<class C>
	void Entity::removeComp() {
		if (!isComp<C>()) {
			Logger::Log(Logger::WARNING, "Trying to remove a component that is not a component type. Will ignore.");
			return;
		}
		for (auto i = components.begin(); i != components.end(); ++i) {
			if ((*i)->type == C::type) {
				compflags.set(C::type, false);
				components.erase(i);
			}
		}
	}

	template<class C>
	Entity::compPtr Entity::addComp(std::initializer_list<std::any> args) {
		if (!isComp<C>()) {
			Logger::Log(Logger::WARNING, "Trying to create a component that is not a component type. Will ignore.");
			return;
		}
		if (!hasComp<C>()) {
			Logger::Log(Logger::WARNING, "Trying to add a component to an entity when one already exists of this type.");
			return;
		}
		compPtr component = std::make_shared<C>(args);
		compflags.set(C::type);
		components.push_back(component);
		return component;
	}

	template<class C>
	Entity::compPtr Entity::getComp() {
		if (!isComp<C>()) {
			Logger::Log(Logger::ERROR, "Trying to get a component that is not a component type!");
			return nullptr;
		}
		for (auto i = components.begin(); i != components.end(); ++i) {
			if ((*i)->type == C::type) return *i;
		}
		Logger::Log(Logger::ERROR, "Cannot find component in entity of ID" + std::to_string(id) + "!");
		return nullptr;
	}
}
