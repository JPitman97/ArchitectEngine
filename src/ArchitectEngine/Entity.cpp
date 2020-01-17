#include "Entity.h"
#include "LuaComponent.h"
#include "Component.h"

Entity::~Entity() = default;

std::shared_ptr<Core> Entity::getCore() const
{
	return core.lock();
}

void Entity::update()
{
	for (auto& comp : components)
	{
		comp->onDisplay();		
		comp->onTick();
	}
}

void Entity::tick()
{
}

void Entity::display()
{
}
