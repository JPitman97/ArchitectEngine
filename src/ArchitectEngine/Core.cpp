#include "Core.h"
#include "Entity.h"
#include <GL/glew.h>
#include "ShaderProgram.h"

std::shared_ptr<Core> Core::Initialize(std::string _title, int _width, int _height)
{
	std::shared_ptr<Core> core = std::make_shared<Core>();
	core->self = core;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::string msg = "Couldn't initialise SDL: ";
		throw std::runtime_error(msg += SDL_GetError());
	}

	SDL_CreateWindowAndRenderer(_width, _height, SDL_WINDOW_OPENGL, &core->window, &core->renderer);
	SDL_SetWindowTitle(core->window, _title.c_str());

	if (!SDL_GL_CreateContext(core->window))
	{
		std::string msg = "Couldn't initialise OpenGL Context: ";
		throw std::runtime_error(msg += SDL_GetError());
	}
	if (glewInit() != GLEW_OK)
	{
		std::string msg = "Couldn't initialise Glew: ";
		throw std::runtime_error(msg += SDL_GetError());
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
			isRunning = false;
			break;
		}

		//Clear the screen to white and also clear the color and depth buffer
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for(auto& entity : entities)
		{
			entity->update();
		}

		SDL_GL_SwapWindow(window);
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
	entity->core = self;
	entities.push_back(entity);
	return entity;
}

std::shared_ptr<ShaderProgram> Core::getShaderProgram() const
{
	return shaderProgram;
}
