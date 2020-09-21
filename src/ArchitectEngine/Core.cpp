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

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(core->window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	return core;
}

void Core::start()
{
	lastTime = glfwGetTime() * 1000;
	quit = false;

	long double accumulator = 0;

	while (!glfwWindowShouldClose(window) && !quit)
	{
		time = glfwGetTime() * 1000;
		diff = time - lastTime;
		Time::deltaTime = diff / 1000.0f;
		lastTime = time;

		// Add the time difference in the accumulator 
		accumulator += Time::deltaTime;

		idealTime = 1.0f / 60.0f;

		// While there is enough accumulated time to take 
		// one or several physics steps 
		while (accumulator >= idealTime)
		{
			// Update the physics world with a constant time step 
			sceneManager->activeScene->world->update(idealTime);

			// Decrease the accumulated time 
			accumulator -= idealTime;
		}

		//Clear the screen to white and also clear the color and depth buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//// Start the Dear ImGui frame
		//ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplGlfw_NewFrame();
		//ImGui::NewFrame();


		for (auto& entity : sceneManager->activeScene->SceneEntities)
		{
			entity->update();
		}
		//// Rendering
		//ImGui::Render();
		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//// Update and Render additional Platform Windows
		//// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		////  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)

		//GLFWwindow* backup_current_context = glfwGetCurrentContext();
		//ImGui::UpdatePlatformWindows();
		//ImGui::RenderPlatformWindowsDefault();
		//glfwMakeContextCurrent(backup_current_context);

		//Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetTime() < lastTime + idealTime)
		{
			//sleep
			std::this_thread::sleep_for((idealTime - Time::deltaTime) * 1000ms);
		}
	}
	//// Cleanup
	//ImGui_ImplOpenGL3_Shutdown();
	//ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
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

std::shared_ptr<Scene> Core::getActiveScene()
{
	return sceneManager->activeScene;
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
