#include "Entity.h"

std::shared_ptr<Core> Entity::getCore() const
{
	return core.lock();
}

void Entity::tick()
{
}

void Entity::display()
{
}
