#include "Component.h"
#include "Entity.h"

Component::Component() = default;

std::shared_ptr<Entity> Component::getEntity() const
{
	return entity.lock();
}

std::shared_ptr<Core> Component::getCore() const
{
	return nullptr;
}

void Component::onInit()
{
}

void Component::onBegin()
{
}

void Component::onTick()
{
}

void Component::onDisplay()
{
}
