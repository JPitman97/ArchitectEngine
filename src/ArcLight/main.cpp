#include <ArchitectEngine/architectengine.h>
#include <iostream>

///This method creates entities and adds components.
///
///This method creates entities and populates them with components before starting the game loop.
int main()
{
	//TODO Entities require RendererComponent otherwise crash

	//Init
	shared<Core> core = Core::Initialize("Arc Light", 1280, 720);
	auto prop = Scene::createWorldPhysicsSettings();
	prop.gravity = { 0, -9.81, 0 };
	prop.isSleepingEnabled = { true };
	shared<Scene> scene1 = core->addScene();
	scene1->addPhysicsWorld(prop);

	shared<Entity> Player = core->addEntity();
	shared<TransformComponent> TC2 = Player->addComponent<TransformComponent>();
	shared<RendererComponent> entityRenderer2 = Player->addComponent<RendererComponent>();
	entityRenderer2->setShader("Shaders/invert.vert", "Shaders/invert.frag");
	entityRenderer2->getShader()->SetUniform("projectionMatrix", core->getDefaultProjectionMatrix());
	entityRenderer2->getShader()->SetUniform("modelMatrix", core->getDefaultModelMatrix());
	entityRenderer2->getShader()->SetUniform("viewMatrix", core->getDefaultViewMatrix());
	TC2->setPos(glm::vec3(0.0f, 5.0f, 5.0f));
	TC2->setRot(glm::vec3(0, 0, 0));
	TC2->setScale(glm::vec3(0.2f));
	Player->addComponent<InputComponent>();
	shared<AudioComponent> AC2 = Player->addComponent<AudioComponent>();
	Player->addComponent<TPCameraComponent>()->initialise();

	shared<Entity> Map = core->addEntity();
	shared<RendererComponent> mRC = Map->addComponent<RendererComponent>();
	mRC->setMesh("Assets/Models/Map.obj");
	shared<TransformComponent> mTC = Map->addComponent<TransformComponent>();
	mTC->setPos(glm::vec3(0.0f, 0.0f, 0.0f));
	mTC->setRot(glm::vec3(0, 0, 0));
	mTC->setScale(glm::vec3(1.0f));
	shared<RigidBodyComponent> mRb = Map->addComponent<RigidBodyComponent>();
	mRb->initialise();
	mRb->setType(RigidBodyComponent::RIGIDBODYTYPE::STATIC);
	mRb->addCollider(RigidBodyComponent::COLLIDERTYPE::BOX, glm::vec3(200, 24, 200));
	mRb->setBounciness(0);

	shared<Entity> testRB = core->addEntity();
	shared<RendererComponent> rbRC = testRB->addComponent<RendererComponent>();
	rbRC->setMesh("Assets/Models/CubeNewTexture.obj");
	shared<TransformComponent> rbTC = testRB->addComponent<TransformComponent>();
	rbTC->setPos(glm::vec3(0.0f, 20.0f, 0.0f));
	rbTC->setRot(glm::vec3(0, 0, 0));
	rbTC->setScale(glm::vec3(1.0f));
	shared<RigidBodyComponent> rb = testRB->addComponent<RigidBodyComponent>();
	rb->initialise();
	rb->setType(RigidBodyComponent::RIGIDBODYTYPE::DYNAMIC);
	rb->addCollider(RigidBodyComponent::COLLIDERTYPE::BOX, glm::vec3(20, 20, 20));
	//Any higher and possibly float precision lost with bounce?
	rb->setBounciness(0.3);
	rb->setMass(5);

	shared<Entity> skybox = core->addEntity();
	shared<RendererComponent> RC = skybox->addComponent<RendererComponent>();
	RC->setShader("Shaders/skybox.vert", "Shaders/skybox.frag");
	RC->getShader()->SetUniform("skybox", 0);
	shared<SkyBoxComponent> SB = skybox->addComponent<SkyBoxComponent>("Assets/Skybox");
	
	core->setActiveScene(scene1); 

	//Start
	core->start();
	std::cout << "Dying" << std::endl;
	return 0;
}
