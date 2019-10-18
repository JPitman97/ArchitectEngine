#ifndef _ENTITY_H
#define _ENTITY_H

#include <memory>
#include <list>

class Component;
class Core;

class Entity
{
public:

	std::shared_ptr<Core> getCore() const;

	template <class T>
	std::shared_ptr<T> addComponent();

private:
	void tick();

	void display();

private:
	std::weak_ptr<Core> core;
	std::list<std::shared_ptr<Component>> components;
};

#endif
