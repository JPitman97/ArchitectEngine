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

///This class handles the creation of entities.
///
///This class handles the creation of entities and the ability to add components to them.
class Entity
{
public:
	friend class Core;

	~Entity();

	///This method returns a shared pointer to the core.
	///
	///method returns a shared pointer to the core for entities to use.
	std::shared_ptr<Core> getCore() const;

	///This template method is used to add components to entities.
	///
	///This template method is used to add components of all types to Entities and then return a shared pointer to them.
	///@param args This is the arguments for the component
	template <typename T, typename... A>
	std::shared_ptr<T> addComponent(A... args)
	{
		std::shared_ptr<T> comp = std::make_shared<T>(args...);
		comp->entity = self;
		components.push_back(comp);

		return comp;
	}

	///This template method is used to retrieve components on entities.
	///
	///This template method is used to retrieve components of all types on Entities and return a shared pointer to them.
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

	///This method is used to run onDisplay and onTick for entities.
	///
	///This method runs onDisplay and onTick every tick for components to update themselves.
	void update();

private:
	///This is the base tick() method.
	///
	///Base tick() method(), used in the future.
	void tick();

	///This is the base display() method.
	///
	///This is the base Display() method, used in the future.
	void display();

private:
	std::weak_ptr<Entity> self;
	std::weak_ptr<Core> core;
	std::list<std::shared_ptr<Component>> components;
};

#endif
