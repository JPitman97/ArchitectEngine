#ifndef _CORE_H
#define _CORE_H

#include <memory>
#include <vector>

class Entity;

class Core
{
public:
	Core();

	~Core();

	static std::shared_ptr<Core> Initialize();

	void start();

	void stop();

	std::shared_ptr<Entity> addEntity();

private:
	//std::shared_ptr<Enviroment> enviroment;
	//std::shared_ptr<Keyboard> keyboard;
	std::vector<std::shared_ptr<Entity>> entities;
	bool isRunning;
};

#endif
