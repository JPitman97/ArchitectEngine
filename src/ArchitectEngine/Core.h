#ifndef _CORE_H
#define _CORE_H

#include <memory>
#include <list>
#include <SDL2/SDL.h>
#include <glm/mat4x2.hpp>

class Entity;
class ShaderProgram;
class Camera;
class Input;

class Core
{
public:
	friend class RendererComponent; //TODO REMOVE THIS

	static std::shared_ptr<Core> Initialize(std::string _title, int _width, int _height);

	void start();

	void stop();

	std::shared_ptr<Entity> addEntity();

	void setModelMatrix(glm::mat4 _modelMatrix) { modelMatrix = _modelMatrix; }
	glm::mat4 getDefaultModelMatrix() const { return modelMatrix; }
	glm::mat4 getDefaultViewMatrix() const { return viewMatrix; }
	glm::mat4 getDefaultProjectionMatrix() const { return projectionMatrix; }

	void setShaderProgram(std::shared_ptr<ShaderProgram> _shaderProgram) { shaderProgram = _shaderProgram; }
	std::shared_ptr<ShaderProgram> getShaderProgram() const;

	std::shared_ptr<Camera> getCamera() const;

	std::shared_ptr<Input> getInput() const;

	std::list<std::shared_ptr<Entity>> getEntities() const;

	glm::vec2 getScreenSize() const;

private:
	std::shared_ptr<ShaderProgram> shaderProgram;
	std::shared_ptr<Camera> camera;
	std::list<std::shared_ptr<Entity>> entities;
	bool isRunning = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	int width, height;
	SDL_Event event;
	std::weak_ptr<Core> self;

	std::shared_ptr<Input> input;

	glm::mat4 modelMatrix, viewMatrix, projectionMatrix;

	float lastTime, time, diff, idealTime;
};

#endif
