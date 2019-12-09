#include <ArchitectEngine/architectengine.h>
#include <iostream>

#define shared std::shared_ptr
#define weak std::weak_ptr

int main()
{
	//Init
	shared<Core> core = Core::Initialize("Arc Light", 800, 600);

	core->setShaderProgram(std::make_shared<ShaderProgram>("Debug/shaders/simple.vert", "Debug/shaders/simple.frag"));
	core->getShaderProgram()->SetUniform("in_Texture", 1);

	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	//set the projectionMatrix to perspective
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

	//update the shader uniform "projectionMatrix" with the new matrix
	core->getShaderProgram()->SetUniform("projectionMatrix", projectionMatrix);
	core->getShaderProgram()->SetUniform("modelMatrix", glm::mat4(1.0f));
	core->getShaderProgram()->SetUniform("viewMatrix", glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2)));

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

	shared<Entity> skybox = core->addEntity();
	shared<RendererComponent> RC = skybox->addComponent<RendererComponent>();
	RC->setShader("Debug/shaders/skybox.vert", "Debug/shaders/skybox.frag");
	RC->getShader()->SetUniform("projectionMatrix", projectionMatrix);
	RC->getShader()->SetUniform("viewMatrix", glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2)));

	shared<SkyBloxComponent> SB = skybox->addComponent<SkyBloxComponent>("Debug/Assets/Skybox");
	


	//Start
	core->start();

	std::cout << "Dying" << std::endl;
	return 0;
}
