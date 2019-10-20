#ifndef _COMPONENT_H
#define _COMPONENT_H
#include <memory>

class Core;
class Entity;

class Component
{
public:
	friend class Entity;

	virtual ~Component() = default;

	std::shared_ptr<Entity> getEntity() const;

	std::shared_ptr<Core> getCore() const;

	//std::shared_ptr<Keyboard> getKeyboard() const;

	//std::shared_ptr<Environment> getEnvironment() const;

private:
	virtual void onInit();
	virtual void onBegin();
	virtual void onTick();
	virtual void onDisplay();


private:
	std::weak_ptr<Entity> entity;
};

#endif