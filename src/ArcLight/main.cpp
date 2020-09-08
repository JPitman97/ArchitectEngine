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
	shared<MeshCollision> BC = Crate->addComponent<MeshCollision>();
	BC->setIsStatic(true);
	//BC->setSize(glm::vec3(0.1f, 0.1f, 0.1f));
	shared<LuaComponent> luaTest = Crate->addComponent<LuaComponent>();
	luaTest->initialise("Assets/Lua/start.lua");
	shared<LuaComponent> luaTest2 = Crate->addComponent<LuaComponent>();
	luaTest2->initialise("Assets/Lua/rotator.lua");
	shared<AudioComponent> AC = Crate->addComponent<AudioComponent>();
	//AC->playAudio("Assets/Kryp.ogg"); //Background audio

	shared<Entity> Crate2 = core->addEntity();
	shared<TransformComponent> TC3 = Crate2->addComponent<TransformComponent>();
	shared<RendererComponent> entityRenderer3 = Crate2->addComponent<RendererComponent>();
	entityRenderer3->setMesh("Assets/Cube.obj", "Assets/Crate.jpg");
	TC3->setPos(glm::vec3(-0.3f, 0.0f, 1.0f));
	TC3->setRot(glm::vec3(0, 0, 0));
	TC3->setScale(glm::vec3(0.2f));
	shared<MeshCollision> BC3 = Crate2->addComponent<MeshCollision>();
	BC3->setIsStatic(true);
	//BC3->setSize(glm::vec3(0.1f, 0.1f, 0.1f));
	shared<LuaComponent> luaTest3 = Crate2->addComponent<LuaComponent>();
	luaTest3->initialise("Assets/Lua/sineMotion.lua");

	shared<Entity> Player = core->addEntity();
	shared<TransformComponent> TC2 = Player->addComponent<TransformComponent>();
	shared<RendererComponent> entityRenderer2 = Player->addComponent<RendererComponent>();
	entityRenderer2->setShader("Shaders/invert.vert", "Shaders/invert.frag");
	entityRenderer2->getShader()->SetUniform("projectionMatrix", core->getDefaultProjectionMatrix());
	entityRenderer2->getShader()->SetUniform("modelMatrix", core->getDefaultModelMatrix());
	entityRenderer2->getShader()->SetUniform("viewMatrix", core->getDefaultViewMatrix());
	entityRenderer2->setMesh("Assets/Cube.obj", "Assets/Crate.jpg");
	TC2->setPos(glm::vec3(1.0f, -0.3f, 0.0f));
	TC2->setRot(glm::vec3(0, 0, 0));
	TC2->setScale(glm::vec3(0.2f));
	Player->addComponent<InputComponent>();
	shared<MeshCollision> BC2 = Player->addComponent<MeshCollision>();
	BC2->setIsStatic(false);
	//BC2->setSize(glm::vec3(0.3f, 0.3f, 0.3f));
	shared<AudioComponent> AC2 = Player->addComponent<AudioComponent>();
	Player->addComponent<TPCameraComponent>()->initialise();

	shared<Entity> skybox = core->addEntity();
	shared<RendererComponent> RC = skybox->addComponent<RendererComponent>();
	RC->setShader("Shaders/skybox.vert", "Shaders/skybox.frag");
	RC->getShader()->SetUniform("skybox", 0);
	shared<SkyBloxComponent> SB = skybox->addComponent<SkyBloxComponent>("Assets/Skybox");

	shared<Scene> scene2 = core->addScene();
	
	core->setActiveScene(scene1); 

	/*glm::vec3 p1 = { -0.323523998f, 1.68264794f, -1.20740700f };
	float p1Arr[3] = { p1.x, p1.y, p1.z };
	glm::vec3 p2 = { -0.478354007f, 1.68264794f, -1.15484905f };
	float p2Arr[3] = { p2.x, p2.y, p2.z };
	glm::vec3 p3 = { -0.465537012f, 1.80764794f, -1.12390494f };
	float p3Arr[3] = { p3.x, p3.y, p3.z };

	glm::vec3 q1 = { 1.00000000f, -0.682647943f, -0.999998987f };
	float q1Arr[3] = { q1.x, q1.y, q1.z };
	glm::vec3 q2 = { 1.00000000f, -2.68264794f, -1.00000000f };
	float q2Arr[3] = { q2.x, q2.y, q2.z };
	glm::vec3 q3 = { -1.00000000f, -0.682647943f, -1.00000000f };
	float q3Arr[3] = { q3.x, q3.y, q3.z };

	int i = Player->getComponent<MeshCollision>()->tri_tri_overlap_test_3d(p1Arr, p2Arr, p3Arr, q1Arr, q2Arr, q3Arr);
	printf("Result = %d\n", i);*/

	//Start
	core->start();

	std::cout << "Dying" << std::endl;
	return 0;
}
