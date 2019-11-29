#ifndef _ENTITY_H
#define _ENTITY_H

#include <memory>
#include <list>

extern "C" {
#include "LUA53/lua.h"
#include "LUA53/lauxlib.h"
#include "LUA53/lualib.h"
}
#include <LuaBridge/LuaBridge.h>

#ifdef _WIN32
//#pragma comment(lib, "liblua53.a")
#endif

class Component;
class LuaComponent;
class Core;

class Entity
{
public:
	friend class Core;

	~Entity();

	std::shared_ptr<Core> getCore() const;


	template <typename T, typename... A>
	std::shared_ptr<T> addComponent(A... args)
	{
		std::shared_ptr<T> comp = std::make_shared<T>(args...);
		comp->entity = self;
		components.push_back(comp);

		return comp;
	}

	template<class T> std::shared_ptr<T> getComponent()
	{
		for (auto& comp : components)
		{
			std::shared_ptr<T> c = std::dynamic_pointer_cast<T>(comp);
			if (c)
				return c;
		}
		return nullptr;
	}

	void update();

	std::shared_ptr<LuaComponent> addLuaComponent(const std::string& _scriptFilename);

private:
	void tick();

	void display();

private:
	std::weak_ptr<Entity> self;
	std::weak_ptr<Core> core;
	std::list<std::shared_ptr<Component>> components;
	std::list<std::shared_ptr<LuaComponent>> luaComponents;


	//Handle Lua logic
	lua_State *lState = nullptr;
};

#endif
