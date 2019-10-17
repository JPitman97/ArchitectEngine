#ifndef _ENTITY_H
#define _ENTITY_H

#include <memory>
#include <vector>

class Core;
class Component;
class Entity
{
public:

	Entity();

	std::shared_ptr<Core> getCore() const;

	template <class T>
	std::shared_ptr<T> addComponent();

private:
	void tick();

	void display();

private:
	std::weak_ptr<Core> core;
	std::vector<std::shared_ptr<Component>> components;
};

#endif
