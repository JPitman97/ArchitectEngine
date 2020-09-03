#include <ArchitectEngine/architectengine.h>
#include <iostream>

///This method creates entities and adds components.
///
///This method creates entities and populates them with components before starting the game loop.
int main()
{
	//Init
	shared<Core> core = Core::Initialize("Arc Light", 1280, 720);
	shared<Scene> scene1 = core->addScene();
	shared<Entity> Crate = core->addEntity();
	shared<TransformComponent> TC = Crate->addComponent<TransformComponent>();
	shared<RendererComponent> entityRenderer = Crate->addComponent<RendererComponent>();
	entityRenderer->setMesh("Assets/Cube.obj", "Assets/Crate.jpg");
	TC->setPos(glm::vec3(-0.3f, 0.0f, 0.0f));
	TC->setRot(glm::vec3(0, 0, 0));
	TC->setScale(glm::vec3(0.2f));
	shared<BoxColliderComponent> BC = Crate->addComponent<BoxColliderComponent>();
	BC->setSize(glm::vec3(0.1f, 0.1f, 0.1f));
	shared<LuaComponent> luaTest = Crate->addComponent<LuaComponent>();
	luaTest->initialise("Assets/Lua/start.lua");
	shared<LuaComponent> luaTest2 = Crate->addComponent<LuaComponent>();
	luaTest2->initialise("Assets/Lua/rotator.lua");
	shared<AudioComponent> AC = Crate->addComponent<AudioComponent>();
	//AC->playAudio("Assets/Kryp.ogg"); //Background audio

	shared<Entity> Crate2 = core->addEntity();
	shared<TransformComponent> TC2 = Crate2->addComponent<TransformComponent>();
	shared<RendererComponent> entityRenderer2 = Crate2->addComponent<RendererComponent>();
	entityRenderer2->setShader("Shaders/invert.vert", "Shaders/invert.frag");
	entityRenderer2->getShader()->SetUniform("projectionMatrix", core->getDefaultProjectionMatrix());
	entityRenderer2->getShader()->SetUniform("modelMatrix", core->getDefaultModelMatrix());
	entityRenderer2->getShader()->SetUniform("viewMatrix", core->getDefaultViewMatrix());	
	entityRenderer2->setMesh("Assets/ivysaur.obj", "Assets/ivysaur_diffuse.jpg");
	TC2->setPos(glm::vec3(1.0f, -0.3f, 0.0f));
	TC2->setRot(glm::vec3(0, 0, 0));
	TC2->setScale(glm::vec3(0.2f));
	Crate2->addComponent<InputComponent>();
	shared<BoxColliderComponent> BC2 = Crate2->addComponent<BoxColliderComponent>();
	BC2->setSize(glm::vec3(0.3f, 0.3f, 0.3f));
	shared<AudioComponent> AC2 = Crate2->addComponent<AudioComponent>();
	Crate2->addComponent<TPCameraComponent>()->initialise();

	shared<Entity> Crate3 = core->addEntity();
	shared<TransformComponent> TC3 = Crate3->addComponent<TransformComponent>();
	shared<RendererComponent> entityRenderer3 = Crate3->addComponent<RendererComponent>();
	entityRenderer3->setMesh("Assets/Cube.obj", "Assets/Crate.jpg");
	TC3->setPos(glm::vec3(-0.1f, 0.0f, 0.0f));
	TC3->setRot(glm::vec3(0, 0, 0));
	TC3->setScale(glm::vec3(0.2f));
	shared<BoxColliderComponent> BC3 = Crate3->addComponent<BoxColliderComponent>();
	BC3->setSize(glm::vec3(0.1f, 0.1f, 0.1f));
	shared<LuaComponent> luaTest3 = Crate3->addComponent<LuaComponent>();
	luaTest3->initialise("Assets/Lua/sineMotion.lua");


	shared<Entity> skybox = core->addEntity();
	shared<RendererComponent> RC = skybox->addComponent<RendererComponent>();
	RC->setShader("Shaders/skybox.vert", "Shaders/skybox.frag");
	RC->getShader()->SetUniform("skybox", 0);
	shared<SkyBloxComponent> SB = skybox->addComponent<SkyBloxComponent>("Assets/Skybox");

	shared<Scene> scene2 = core->addScene();

	//Start
	core->start();

	std::cout << "Dying" << std::endl;
	return 0;
}
