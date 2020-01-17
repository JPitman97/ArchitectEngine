#ifndef _COMPONENT_H
#define _COMPONENT_H
#include <memory>

class Core;
class Entity;

///This class handles the components.
///
///This method handles retreiving the component entity as well as the core, plus it provides virtual methods.
class Component
{
public:
	friend class Entity;

	virtual ~Component() = default;

	///This method returns the component entity.
	///
	///This method returns a shared pointer to the entity.
	std::shared_ptr<Entity> getEntity() const;

	///This method returns the Core.
	///
	///This method returns a shared Core pointer.
	std::shared_ptr<Core> getCore() const;

private:
	///This method is used to allow overloading of onInit().
	///
	///This method can be overloaded by components to run at start.
	virtual void onInit();
	///This method is used to allow overloading of onBegin().
	///
	///This method can be overloaded by components to run just after start.
	virtual void onBegin();
	///This method is used to overload onTick().
	///
	///This method can be overloaded by components to run every tick.
	virtual void onTick();
	///This method is used to overload onDisplay.
	///
	///This method can be overloaded by components to draw objects.
	virtual void onDisplay();


private:
	std::weak_ptr<Entity> entity;
	std::weak_ptr<Core> core;
};

#endif