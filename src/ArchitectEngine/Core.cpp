#include "Core.h"
#include "Entity.h"
#include "ShaderProgram.h"
#include "TransformComponent.h"
#include "Time.h"
#include "Camera.h"
#include "Input.h"
#include "SceneManager.h"

std::shared_ptr<Core> Core::Initialize(std::string _title, int _width, int _height)
{
	std::shared_ptr<Core> core = std::make_shared<Core>();
	core->self = core;

	if (!glfwInit()) {
		std::string msg = "Couldn't initialise GLFW: ";
		throw std::runtime_error(msg);
	}

	core->window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
	if (!core->window)
	{
		std::string msg = "Couldn't create window: ";
		throw std::runtime_error(msg);
	}

	glfwMakeContextCurrent(core->window);
	glfwSetWindowUserPointer(core->window, reinterpret_cast<void*>(core.get()));

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		std::cerr << "Error: Loading GLAD" << std::endl;
	}

	core->input = std::make_shared<Input>();

	// tell GLFW to capture our mouse
	glfwSetInputMode(core->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Callbacks
	glfwSetFramebufferSizeCallback(core->window, core->framebuffer_size_callback);
	glfwSetCursorPosCallback(core->window, core->input->mouse_callback);
	//glfwSetScrollCallback(core->window, core->scroll_callback);
	glfwSetKeyCallback(core->window, core->input->handleInput);

	core->setShaderProgram(std::make_shared<ShaderProgram>("Shaders/simple.vert", "Shaders/simple.frag"));
	core->getShaderProgram()->SetUniform("in_Texture", 1);
	core->input = std::make_shared<Input>();

	core->sceneManager = std::make_unique<SceneManager>();

	// camera 
	core->camera = std::make_shared<Camera>(glm::vec3(0.0F, 0.0f, 3.0f));

	core->width = _width;
	core->height = _height;

	//update the shader uniform "projectionMatrix" with the new matrix
	core->modelMatrix = glm::mat4(1.0f);
	core->viewMatrix = core->getCamera()->getViewMatrix();
	core->projectionMatrix = glm::perspective(glm::radians(core->getCamera()->Zoom), (float)core->getScreenSize().x / (float)core->getScreenSize().y, 0.1f, 100.0f);
	core->getShaderProgram()->SetUniform("projectionMatrix", core->projectionMatrix);
	core->getShaderProgram()->SetUniform("modelMatrix", core->modelMatrix);
	core->getShaderProgram()->SetUniform("viewMatrix", core->viewMatrix);

	return core;
}

#include <reactphysics3d/reactphysics3d.h>
void Core::start()
{
	lastTime = glfwGetTime() * 1000;
	quit = false;

	reactphysics3d::PhysicsCommon physicsCommon;
	reactphysics3d::PhysicsWorld* world = physicsCommon.createPhysicsWorld();
	reactphysics3d::Vector3 position(0, 20, 0);
	reactphysics3d::Quaternion orientation = reactphysics3d::Quaternion::identity();
	reactphysics3d::Transform transform(position, orientation);
	reactphysics3d::RigidBody* body = world->createRigidBody(transform);

	while (!glfwWindowShouldClose(window) && !quit)
	{
		time = glfwGetTime() * 1000;
		diff = time - lastTime;
		Time::deltaTime = diff / 1000.0f;
		lastTime = time;

		world->update(Time::deltaTime);
		// Get the updated position of the body 
		const reactphysics3d::Transform& transform = body->getTransform();
		const reactphysics3d::Vector3& position = transform.getPosition();

		// Display the position of the body 
		std::cout << "Body Position: (" << position.x << ", " <<
			position.y << ", " << position.z << ")" << std::endl;

		//Clear the screen to white and also clear the color and depth buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto& entity : sceneManager->activeScene->SceneEntities)
		{
			entity->update();
		}

		//Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		idealTime = 1.0f / 60.0f;
		if (glfwGetTime() < lastTime + idealTime)
		{
			//sleep
			std::this_thread::sleep_for((idealTime - Time::deltaTime) * 1000ms);
		}
	}
}

std::shared_ptr<Entity> Core::addEntity()
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	entity->self = entity;
	entity->core = self;
	sceneManager->activeScene->SceneEntities.push_back(entity);
	return entity;
}

std::shared_ptr<Scene> Core::addScene()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	sceneManager->setActiveScene(scene);

	return scene;
}

void Core::setActiveScene(std::shared_ptr<Scene> _scene)
{
	sceneManager->setActiveScene(_scene);
}

std::shared_ptr<ShaderProgram> Core::getShaderProgram() const
{
	return shaderProgram;
}

std::shared_ptr<Camera> Core::getCamera() const
{
	return camera;
}

void Core::setCamera(std::shared_ptr<Camera> _camera)
{
	camera = _camera;
}

std::shared_ptr<Input> Core::getInput() const
{
	return input;
}

std::vector<std::shared_ptr<Entity>> Core::getEntities() const
{
	return sceneManager->activeScene->SceneEntities;
}

glm::vec2 Core::getScreenSize() const
{
	return glm::vec2(width, height);
}

void Core::shouldQuit(bool _shouldQuit)
{
	quit = _shouldQuit;
}

void Core::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
