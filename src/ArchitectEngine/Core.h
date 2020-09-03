#ifndef _CORE_H
#define _CORE_H

#include <memory>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x2.hpp>
#include <string>
#include <chrono>
#include <thread>
using namespace std::literals::chrono_literals;

class Entity;
class ShaderProgram;
class Camera;
class Input;
class SceneManager;
class Scene;

///This class is the main class that groups everything together.
///
///This class handles the run loop as well as the starting and stopping of the game, as well as adding entities.
class Core
{
public:
	friend class RendererComponent;

	///This method initializes the engine with an SDL window, renderer and context.
	///
	///This method also initializes the core shaders and input variables, along with the camera.
	///@param _title This is the window title
	///@param _width This is the width of the window.
	///@param _height This is the height of the window.
	static std::shared_ptr<Core> Initialize(std::string _title, int _width, int _height);

	///This method starts the game loop of the engine.
	///
	///This method starts the game loop as well as initializing the deltaTime variable within Time
	void start();

	///This method adds a new entity.
	///
	///This method adds a new entity and specifies values for self and core, as well as pushing the entity onto a vector.
	std::shared_ptr<Entity> addEntity();

	std::shared_ptr<Scene> addScene();

	///This method sets the default model matrix for the engine.
	///
	///This method sets the model matrix for new components.
	///@param _modelMatrix This is the default model matrix.
	void setModelMatrix(glm::mat4 _modelMatrix) { modelMatrix = _modelMatrix; }

	///This method gets the default model matrix.
	///
	///This method returns the model matrix.
	glm::mat4 getDefaultModelMatrix() const { return modelMatrix; }
	///This method gets the default view matrix.
	///
	///This method returns the view matrix.
	glm::mat4 getDefaultViewMatrix() const { return viewMatrix; }
	///This method gets the projection model matrix.
	///
	///This method returns the projection matrix.
	glm::mat4 getDefaultProjectionMatrix() const { return projectionMatrix; }

	///This method sets the shader program for the core.
	///
	///This method sets a default shader program for the core.
	///@param _shaderProgram This is the new shader program
	void setShaderProgram(std::shared_ptr<ShaderProgram> _shaderProgram) { shaderProgram = _shaderProgram; }

	///This method gets the default shader program.
	///
	///This method returns the model matrix.
	std::shared_ptr<ShaderProgram> getShaderProgram() const;

	///This method gets the default camera.
	///
	///This method returns the camera.
	std::shared_ptr<Camera> getCamera() const;

	void setCamera(std::shared_ptr<Camera> _camera);

	///This method gets the Input object.
	///
	///This method returns the Input object to allow for handling of key presses.
	std::shared_ptr<Input> getInput() const;

	///This method gets the entities list.
	///
	///This method returns the entities list so it can be iterated through.
	std::vector<std::shared_ptr<Entity>> getEntities() const;

	///This method gets the default screen size.
	///
	///This method returns the screen size set during initialization.
	glm::vec2 getScreenSize() const;

	void shouldQuit(bool _shouldQuit);

private:
	// Callbacks
	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	std::shared_ptr<ShaderProgram> shaderProgram;
	std::shared_ptr<Camera> camera;
	std::unique_ptr<SceneManager> sceneManager;

	bool isRunning = false;
	GLFWwindow* window = nullptr;
	int width, height;
	std::weak_ptr<Core> self;

	std::shared_ptr<Input> input;

	glm::mat4 modelMatrix, viewMatrix, projectionMatrix;

	double lastTime, time, diff, idealTime = 0;
};

#endif
