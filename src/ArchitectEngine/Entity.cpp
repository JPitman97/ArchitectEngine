#include "Entity.h"

std::shared_ptr<Core> Entity::getCore() const
{
	return core.lock();
}

template <class T>
std::shared_ptr<T> Entity::addComponent()
{
	std::shared_ptr<T> comp;
	components.push_back(comp);
	return comp;
}

void Entity::tick()
{
}

void Entity::display()
{
}
