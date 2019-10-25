#ifndef _ENTITY_H
#define _ENTITY_H

#include <memory>
#include <list>

class Component;
class Core;

class Entity
{
public:
	friend class Core;

	std::shared_ptr<Core> getCore() const;


	template <typename T, typename... A>
	std::shared_ptr<T> addComponent(A... args)
	{
		std::shared_ptr<T> comp = std::make_shared<T>(args...);
		comp->entity = self;
		components.push_back(comp);

		return comp;
	}

private:
	void tick();

	void display();

private:
	std::weak_ptr<Entity> self;
	std::weak_ptr<Core> core;
	std::list<std::shared_ptr<Component>> components;
};

#endif
