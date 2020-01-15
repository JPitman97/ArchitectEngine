#include <ArchitectEngine/architectengine.h>
#include <iostream>

#define shared std::shared_ptr
#define weak std::weak_ptr

int main()
{
	//Init
	shared<Core> core = Core::Initialize("Arc Light", 1280, 720);

	//Create a new entity
	//shared<Entity> entity = core->addEntity();
	//Add a component
	//shared<LuaComponent> luaTest = entity->addLuaComponent("Debug/test.lua");
	//auto TC = entity->addComponent<TransformComponent>();
	//shared<RendererComponent> entityRenderer = entity->addComponent<RendererComponent>();
	//entityRenderer->setMesh("Debug/Assets/Cube.obj", "Debug/Assets/Crate.jpg");
	//TC->setPos(glm::vec3(-0.3f, 0.0f, 0.0f));
	//TC->setRot(glm::vec3(0, 0, 0));
	//TC->setScale(glm::vec3(0.2f));

	
	shared<Entity> Crate = core->addEntity();
	auto TC = Crate->addComponent<TransformComponent>();
	shared<RendererComponent> entityRenderer = Crate->addComponent<RendererComponent>();
	entityRenderer->setMesh("Assets/Cube.obj", "Assets/Crate.jpg");
	TC->setPos(glm::vec3(-0.3f, 0.0f, 0.0f));
	TC->setRot(glm::vec3(0, 0, 0));
	TC->setScale(glm::vec3(0.2f));

	shared<Entity> Crate2 = core->addEntity();
	auto TC2 = Crate2->addComponent<TransformComponent>();
	shared<RendererComponent> entityRenderer2 = Crate2->addComponent<RendererComponent>();
	entityRenderer2->setShader("Shaders/invert.vert", "Shaders/invert.frag");
	entityRenderer2->getShader()->SetUniform("projectionMatrix", core->getDefaultProjectionMatrix());
	entityRenderer2->getShader()->SetUniform("modelMatrix", core->getDefaultModelMatrix());
	entityRenderer2->getShader()->SetUniform("viewMatrix", core->getDefaultViewMatrix());	
	entityRenderer2->setMesh("Assets/ivysaur.obj", "Assets/ivysaur_diffuse.jpg");
	TC2->setPos(glm::vec3(1.0f, -0.3f, 0.0f));
	TC2->setRot(glm::vec3(0, 180, 0));
	TC2->setScale(glm::vec3(0.5f));
	Crate2->addComponent<InputComponent>();


	shared<Entity> skybox = core->addEntity();
	shared<RendererComponent> RC = skybox->addComponent<RendererComponent>();
	RC->setShader("Shaders/skybox.vert", "Shaders/skybox.frag");
	RC->getShader()->SetUniform("skybox", 0);
	shared<SkyBloxComponent> SB = skybox->addComponent<SkyBloxComponent>("Assets/Skybox");

	//Start
	core->start();

	std::cout << "Dying" << std::endl;
	return 0;
}
