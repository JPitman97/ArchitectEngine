#include "Core.h"
#include "Entity.h"
#include <GL/glew.h>

std::shared_ptr<Core> Core::Initialize(int _width, int _height)
{
	std::shared_ptr<Core> core = std::make_shared<Core>();
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialise SDL: %s", SDL_GetError());
		throw std::exception();
	}

	SDL_CreateWindowAndRenderer(_width, _height, SDL_WINDOW_OPENGL, &core->window, &core->renderer);

	if (!SDL_GL_CreateContext(core->window))
	{
		throw std::exception();
	}
	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}

	return core;
}

void Core::start()
{
	isRunning = true;

	while (isRunning)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			break;
		}
	}
}

void Core::stop()
{
	isRunning = false;
}

std::shared_ptr<Entity> Core::addEntity()
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	entity->self = entity;
	entities.push_back(entity);
	return entity;
}
