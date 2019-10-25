#ifndef _CORE_H
#define _CORE_H

#include <memory>
#include <list>
#include <SDL2/SDL.h>

class Entity;

class Core
{
public:
	friend class RendererComponent; //TODO REMOVE THIS

	static std::shared_ptr<Core> Initialize(std::string _title, int _width, int _height);

	void start();

	void stop();

	std::shared_ptr<Entity> addEntity();

private:
	//std::shared_ptr<Enviroment> enviroment;
	//std::shared_ptr<Keyboard> keyboard;
	std::list<std::shared_ptr<Entity>> entities;
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;
	std::weak_ptr<Core> self;
};

#endif
