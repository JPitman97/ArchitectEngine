#include <ArchitectEngine/architectengine.h>
#include <iostream>

#define shared std::shared_ptr
#define weak std::weak_ptr

int main()
{
	//Init
	shared<Core> core = Core::Initialize("Hello Triangle", 640, 480);

	core->setShaderProgram(std::make_shared<ShaderProgram>("shaders/simple.vert", "shaders/simple.frag"));
	core->getShaderProgram()->SetUniform("in_Texture", 1);

	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	//set the projectionMatrix to perspective
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f);

	//update the shader uniform "projectionMatrix" with the new matrix
	core->getShaderProgram()->SetUniform("projectionMatrix", projectionMatrix);

	//Create a new entity
	shared<Entity> entity = core->addEntity();

	//Add a component
	//shared<RendererComponent> entityRenderer = entity->addComponent<RendererComponent>();
	//shared<LuaComponent> luaTest = entity->addLuaComponent("test.lua");
	entity->addComponent<TransformComponent>();
	shared<RendererComponent> entityRenderer = entity->addComponent<RendererComponent>();
	entityRenderer->setMesh("Assets/lumberJack.obj", "Assets/lumberJack_diffuse.png");
	entity->getComponent<TransformComponent>()->setPos(glm::vec3(0.0f, 0.0f, 0.0f));
	entity->getComponent<TransformComponent>()->setRot(glm::vec3(0, 0, 0));
	entity->getComponent<TransformComponent>()->setScale(glm::vec3(1.0f));


	//entityRenderer->onDisplay();
	entity->getComponent<RendererComponent>()->onDisplay();

	//Start
	core->start();

	std::cout << "Dying" << std::endl;
	return 0;
}
