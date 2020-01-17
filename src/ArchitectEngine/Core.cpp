#include "Core.h"
#include "Entity.h"
#include <GL/glew.h>
#include "ShaderProgram.h"
#include "TransformComponent.h"
#include "Time.h"
#include "Camera.h"
#include "Input.h"

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

	std::cout << glGetString(GL_VERSION) << std::endl;

	if (glewInit() != GLEW_OK)
	{
		std::string msg = "Couldn't initialise Glew: ";
		throw std::runtime_error(msg += SDL_GetError());
	}

	core->setShaderProgram(std::make_shared<ShaderProgram>("Shaders/simple.vert", "Shaders/simple.frag"));
	core->getShaderProgram()->SetUniform("in_Texture", 1);

	core->input = std::make_shared<Input>();

	// camera 
	core->camera = std::make_shared<Camera>(glm::vec3(0.0F, 0.0f, 3.0f));

	core->width = _width;
	core->height = _height;

	//update the shader uniform "projectionMatrix" with the new matrix
	core->modelMatrix = glm::mat4(1.0f);
	core->viewMatrix = core->getCamera()->GetViewMatrix();
	core->projectionMatrix = glm::perspective(glm::radians(core->getCamera()->Zoom), (float)core->getScreenSize().x / (float)core->getScreenSize().y, 0.1f, 100.0f);
	core->getShaderProgram()->SetUniform("projectionMatrix", core->projectionMatrix);
	core->getShaderProgram()->SetUniform("modelMatrix", core->modelMatrix);
	core->getShaderProgram()->SetUniform("viewMatrix", core->viewMatrix);

	return core;
}

void Core::start()
{
	lastTime = SDL_GetTicks();
	isRunning = true;

	while (isRunning)
	{
		if (!input->handleInput(&event))
			stop();

		time = SDL_GetTicks();
		diff = time - lastTime;
		Time::deltaTime = diff / 1000.0f;
		lastTime = time;

		//Clear the screen to white and also clear the color and depth buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for(auto& entity : entities)
		{
			entity->update();
		}
	
		SDL_GL_SwapWindow(window);

		idealTime = 1.0f / 60.0f;
		if (idealTime > Time::deltaTime)
		{
			//sleep
			SDL_Delay((idealTime - Time::deltaTime) * 1000.0f);
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
	entity->core = self;
	entities.push_back(entity);
	return entity;
}

std::shared_ptr<ShaderProgram> Core::getShaderProgram() const
{
	return shaderProgram;
}

std::shared_ptr<Camera> Core::getCamera() const
{
	return camera;
}

std::shared_ptr<Input> Core::getInput() const
{
	return input;
}

std::list<std::shared_ptr<Entity>> Core::getEntities() const
{
	return entities;
}

glm::vec2 Core::getScreenSize() const
{
	return glm::vec2(width, height);
}
