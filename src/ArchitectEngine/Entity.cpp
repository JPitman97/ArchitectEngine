#include "Entity.h"
#include "LuaComponent.h"

std::shared_ptr<Core> Entity::getCore() const
{
	return core.lock();
}

std::shared_ptr<LuaComponent> Entity::addLuaComponent(const std::string& _scriptFilename, const std::string& _tableName) const
{
	std::shared_ptr<LuaComponent> lComp = std::make_shared<LuaComponent>();

	return lComp;
}

void Entity::tick()
{
}

void Entity::display()
{
}
