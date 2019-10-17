#include "Core.h"
#include "Entity.h"

Core::Core() = default;

Core::~Core() = default;;

std::shared_ptr<Core> Core::Initialize()
{
	return std::shared_ptr<Core>();
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
	return nullptr;
}
