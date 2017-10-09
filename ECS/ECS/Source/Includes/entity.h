#pragma once

#include <bitset>
#include <memory>
#include <vector>
#include <any>

#include "constants.h"
#include "component.h"
#include "logger.h"

namespace ecs {
	// An Entity is a grouping of Components. An Entity can only have one of each Component type.
	class Entity {
	public:
		typedef std::shared_ptr<Component> compPtr;
		typedef std::vector<compPtr> compList;
		typedef uint64_t idType;

		Entity(idType id) : id(id) {}

		//Entity ID
		const idType id;

		//Testing to see if an Entity contains a specific Component
		template <class C> bool hasComp() const;
		template <class C1, class C2, class... More> bool hasComp() const;

		//Testing to see if template type is a valid component 
		template <class C> bool testComp() const;

		//Removing Components
		template <class C> void removeComp();
		template <class C>
		void clear();

		//Component manipulation
		
		// Add an already existing component to an entity.
		compPtr addComp(const Component& component);
		template <class C> compPtr newComp(std::initializer_list<std::any> args);
		template <class C> compPtr newComp();
		template <class C> compPtr getComp() const;

		~Entity();
	private:
		compList components;
		std::bitset<static_cast<size_t>(consts::ComponentType::NUM_TYPES)> compflags;
	};

	template<class C>
	bool Entity::hasComp() const {
		if (!isComp<C>()) {
			Logger::Log(Logger::ERROR, "Trying to detect a component that is not a component type. Will ignore.");
			return false;
		}
		if (compflags.test(C::type)) return true;
		return false;
	}

	template <class C1, class C2, class ... More>
	bool Entity::hasComp() const {
		return hasComp<C1>() && hasComp<C2, More ...>();
	}

	template<class C>
	bool Entity::testComp() const
	{
		if (!isComp<C>()) {
			Logger::Log(Logger::WARNING, "Trying to create a component that is not a component type. Will ignore.");
			return false;
		}
		if (!hasComp<C>()) {
			Logger::Log(Logger::WARNING, "Trying to add a component to an entity when one already exists of this type.");
			return false;
		}
		return true;
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

	template <class C>
	Entity::compPtr Entity::newComp() {
		if (!testComp<C>()) return;
		compPtr component = std::make_shared<C>();
		compflags.set(C::type);
		components.push_back(component);
		return component;
	}

	template<class C>
	Entity::compPtr Entity::newComp(std::initializer_list<std::any> args) {
		if (!testComp<C>()) return;
		try {
			compPtr component = std::make_shared<C>(args);
			compflags.set(C::type);
			components.push_back(component);
			return component;
		}
		catch (std::exception ex){
			Logger::Log(Logger::Level::ERROR, ex.what());
			return nullptr;
		}
	}

	template<class C>
	Entity::compPtr Entity::getComp() const {
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
