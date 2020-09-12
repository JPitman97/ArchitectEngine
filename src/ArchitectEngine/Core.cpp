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
#include "RendererComponent.h"
void Core::start()
{
	lastTime = glfwGetTime() * 1000;
	quit = false;

	rp3d::PhysicsCommon physicsCommon;
	rp3d::PhysicsWorld* world = physicsCommon.createPhysicsWorld();

	// Gravity vector in the physics world
	rp3d::Vector3 gravity(0, rp3d::decimal(-9.81), 0);
	world->setGravity(gravity);
	rp3d::Vector3 position(0, 20, 0);
	rp3d::Quaternion orientation = reactphysics3d::Quaternion::identity();
	rp3d::Transform transform(position, orientation);
	rp3d::RigidBody* body = world->createRigidBody(transform);
	body->setType(reactphysics3d::BodyType::DYNAMIC);
	body->setMass(20);
	body->setAngularDamping(1.0);
	body->setLinearDamping(0.3);

	std::shared_ptr<Entity> Crate2 = addEntity();
	std::shared_ptr<TransformComponent> TC3 = Crate2->addComponent<TransformComponent>();
	std::shared_ptr<RendererComponent> entityRenderer3 = Crate2->addComponent<RendererComponent>();
	entityRenderer3->setMesh("Assets/Cube.obj", "Assets/Crate.jpg");
	//TC3->setPos(glm::vec3(-0.3f, 0.0f, 1.0f));
	TC3->setRot(glm::vec3(0, 0, 0));
	TC3->setScale(glm::vec3(1.0f));
	// Half extents of the box in the x, y and z directions 
	const reactphysics3d::Vector3 halfExtents(10.0, 10.0, 10.0);
	// Create the box shape 
	rp3d::BoxShape* boxShape = physicsCommon.createBoxShape(halfExtents);
	body->addCollider(boxShape, transform);
	//TODO fix why this is bouncing and acting strangely, maybe need to update library? 
	std::shared_ptr<Entity> Map = addEntity();
	std::shared_ptr<TransformComponent> transComp = Map->addComponent<TransformComponent>();
	std::shared_ptr<RendererComponent> er = Map->addComponent<RendererComponent>();
	er->setMesh("Assets/Map.obj", "Assets/Crate.jpg");
	transComp->setPos(glm::vec3(0, 0.0f, 0.0f));
	transComp->setRot(glm::vec3(0, 0, 0));
	transComp->setScale(glm::vec3(1.0f));
	rp3d::Vector3 position2(0, 0.0f, 0.0f);
	rp3d::Quaternion orientation2 = reactphysics3d::Quaternion::identity();
	rp3d::Transform MapTrans(position2, orientation2);
	rp3d::RigidBody* mapRB = world->createRigidBody(MapTrans);
	mapRB->setType(rp3d::BodyType::STATIC);
	// Half extents of the box in the x, y and z directions 
	const rp3d::Vector3 halfExtents2(100.0, 12, 100.0);
	// Create the box shape 
	rp3d::BoxShape* boxShape2 = physicsCommon.createBoxShape(halfExtents2);
	mapRB->addCollider(boxShape2, MapTrans);

	long double accumulator = 0;
	long double previousFrameTime = 0;

	while (!glfwWindowShouldClose(window) && !quit)
	{
		/*time = glfwGetTime() * 1000;
		diff = time - lastTime;
		Time::deltaTime = diff / 1000.0f;
		lastTime = time;

		// Add the time difference in the accumulator 
		accumulator += Time::deltaTime;

		const reactphysics3d::Transform& oldTrans = body->getTransform();

		idealTime = 1.0f / 60.0f;
		// While there is enough accumulated time to take 
		// one or several physics steps 
		while (accumulator >= idealTime) {

			// Update the physics world with a constant time step 
			world->update(idealTime);

			// Decrease the accumulated time 
			accumulator -= idealTime;
		}
		// Compute the time interpolation factor 
		double factor = accumulator / idealTime;
		// Get the updated position of the body 
		const reactphysics3d::Transform& transform = body->getTransform();
		rp3d::Transform interpolatedTransform = rp3d::Transform::interpolateTransforms(oldTrans,
			transform, factor);
		const reactphysics3d::Vector3& position = interpolatedTransform.getPosition();
		TC3->setPos(glm::vec3(position.x, position.y, position.z));
		if (body->isSleeping())
		{
			std::cout << "Body is sleeping" << std::endl;
		}

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

		if (glfwGetTime() < lastTime + idealTime)
		{
			//sleep
			std::this_thread::sleep_for((idealTime - Time::deltaTime) * 1000ms);
		}*/

		// Constant physics time step 
		const float timeStep = 1.0 / 60.0;

		// Get the current system time 
		long double currentFrameTime = glfwGetTime();

		// Compute the time difference between the two frames 
		long double deltaTime = currentFrameTime - previousFrameTime;
		Time::deltaTime = deltaTime;

		// Update the previous time 
		previousFrameTime = currentFrameTime;

		// Add the time difference in the accumulator 
		accumulator += deltaTime;

		// Get the previous transform of the body 
		rp3d::Transform prevTransform = body->getTransform();

		// While there is enough accumulated time to take 
		// one or several physics steps 
		while (accumulator >= timeStep) {

			// Update the physics world with a constant time step 
			world->update(timeStep);

			// Decrease the accumulated time 
			accumulator -= timeStep;
		}

		// Compute the time interpolation factor 
		rp3d::decimal factor = accumulator / timeStep;

		// Get the updated transform of the body 
		rp3d::Transform currTransform = body->getTransform();

		// Compute the interpolated transform of the rigid body 
		rp3d::Transform interpolatedTransform = rp3d::Transform::interpolateTransforms(prevTransform,
			currTransform, factor);
		auto trans = interpolatedTransform.getPosition();
		// Display the position of the body 
		std::cout << "Body Position: (" << trans.x << ", " <<
			trans.y << ", " << trans.z << ")" << std::endl;
		if (body->isSleeping())
		{
			std::cout << "Body is sleeping" << std::endl;
		}
		// Now you can render your body using the interpolated transform here 
		Crate2->getComponent<TransformComponent>()->setPos(glm::vec3(trans.x, trans.y, trans.z));
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
		// Update the previous transform 
		prevTransform = currTransform;
	}
	// Destroy a rigid body 
	world->destroyRigidBody(body);
	world->destroyRigidBody(mapRB);

	// Destroy a physics world 
	physicsCommon.destroyPhysicsWorld(world);
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
