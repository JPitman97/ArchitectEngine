#include "Core.h"
#include "Entity.h"

std::shared_ptr<Core> Core::Initialize()
{
	std::shared_ptr<Core> core;
	return core;
}

void Core::start()
{
	isRunning = true;
}

void Core::stop()
{
	isRunning = false;
}

std::shared_ptr<Entity> Core::addEntity()
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	entities.push_back(entity);
	return entity;
}
