#ifndef _CORE_H
#define _CORE_H

#include <memory>
#include <list>
#include <SDL2/SDL.h>
#include <glm/mat4x2.hpp>

class Entity;
class ShaderProgram;
class Camera;

class Core
{
public:
	friend class RendererComponent; //TODO REMOVE THIS

	static std::shared_ptr<Core> Initialize(std::string _title, int _width, int _height);

	void start();

	void stop();

	std::shared_ptr<Entity> addEntity();

	glm::mat4 getModelMatrix() const { return modelMatrix; }
	void setModelMatrix(const glm::mat4& _modelMatrix) { modelMatrix = _modelMatrix; }

	void setShaderProgram(std::shared_ptr<ShaderProgram> _shaderProgram) { shaderProgram = _shaderProgram; }
	std::shared_ptr<ShaderProgram> getShaderProgram() const;

	std::shared_ptr<Camera> getCamera() const;

private:
	//std::shared_ptr<Enviroment> enviroment;
	//std::shared_ptr<Keyboard> keyboard;
	std::shared_ptr<ShaderProgram> shaderProgram;
	std::shared_ptr<Camera> camera;
	std::list<std::shared_ptr<Entity>> entities;
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;
	std::weak_ptr<Core> self;

	glm::mat4 modelMatrix;

	float lastTime, time, diff, idealTime;
};

#endif
