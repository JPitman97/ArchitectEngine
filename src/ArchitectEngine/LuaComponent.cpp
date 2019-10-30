#include "LuaComponent.h"

LuaComponent::LuaComponent()
= default;

int LuaComponent::onInit(lua_State* L)
{
	lua_pcall(L, 0, LUA_MULTRET, 0);
	lua_getglobal(L, "onInit");
	lua_pcall(L, 0, 0, 0);
	return 0;
}

int LuaComponent::onBegin(lua_State* L)
{
	lua_pcall(L, 0, LUA_MULTRET, 0);
	lua_getglobal(L, "onBegin");
	lua_pcall(L, 0, 0, 0);
	return 0;
}

int LuaComponent::onTick(lua_State* L)
{
	lua_pcall(L, 0, LUA_MULTRET, 0);
	lua_getglobal(L, "onTick");
	lua_pcall(L, 0, 0, 0);
	return 0;
}

int LuaComponent::onDisplay(lua_State* L)
{
	lua_pcall(L, 0, LUA_MULTRET, 0);
	lua_getglobal(L, "onDisplay");
	lua_pcall(L, 0, 0, 0);
	return 0;
}
