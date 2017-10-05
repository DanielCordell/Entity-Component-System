#include "Includes/logger.h"
#include "Includes/entitymanager.h"
#include "Includes/entity.h"
#include "Includes/component.h"
#include "Includes/constants.h"

int main()
{
	ecs::EntityManager manager;
	auto e = manager.createEntity();
	e->newComp();
	e->addComp<ecs::Component>(std::initializer_list<std::any>());

}