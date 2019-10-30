#include "Entity.h"
#include "LuaComponent.h"
#include "Component.h"

Entity::~Entity()
{
	if (lState != nullptr)
	{
		lua_close(lState);
		lState = nullptr;
	}
}

std::shared_ptr<Core> Entity::getCore() const
{
	return core.lock();
}

void Entity::update()
{
	for each (auto& comp in components)
	{
		comp->onTick();
	}
	for each (auto& comp in luaComponents)
	{
		if (lState)
		{
			comp->onInit(lState);
			comp->onTick(lState);
		}
	}
}

std::shared_ptr<LuaComponent> Entity::addLuaComponent(const std::string& _scriptFilename)
{
	std::shared_ptr<LuaComponent> lComp = std::make_shared<LuaComponent>();

	lState = luaL_newstate();
	luaL_openlibs(lState);
	lua_register(lState, "onInit", lComp->onInit);
	lua_register(lState, "onBegin", lComp->onBegin);
	lua_register(lState, "onTick", lComp->onTick);
	lua_register(lState, "onDisplay", lComp->onDisplay);
	
	luaL_loadfile(lState, _scriptFilename.c_str());
	luaComponents.push_back(lComp);
	return lComp;
}

void Entity::tick()
{
}

void Entity::display()
{
}
