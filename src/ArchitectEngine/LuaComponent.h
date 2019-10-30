#ifndef _LUACOMPONENT_H
#define _LUACOMPONENT_H

extern "C" {
#include "LUA53/lua.h"
#include "LUA53/lauxlib.h"
#include "LUA53/lualib.h"
}
#include <LuaBridge/LuaBridge.h>

#ifdef _WIN32
#pragma comment(lib, "liblua53.a")
#endif

class LuaComponent
{
public:
	LuaComponent();

	static int onInit(lua_State* L);
	static int onBegin(lua_State* L);
	static int onTick(lua_State* L);
	static int onDisplay(lua_State* L);

private:

};

#endif