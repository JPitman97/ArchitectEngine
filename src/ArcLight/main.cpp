#include <ArchitectEngine/architectengine.h>
#include <iostream>

#define shared std::shared_ptr
#define weak std::weak_ptr

int main()
{
	//Init
	shared<Core> core = Core::Initialize(640, 480);

	//Create a new entity
	shared<Entity> entity = core->addEntity();

	//Add a component
	shared<RendererComponent> entityRenderer = entity->addComponent<RendererComponent>();

	entityRenderer->onDisplay();

	//Start
	core->start();

	std::cout << "Dying" << std::endl;
	return 0;
}
