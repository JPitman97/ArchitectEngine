#include "../ArchitectEngine/architectengine.h"
#include <iostream>

#define shared std::shared_ptr
#define weak std::weak_ptr

int main()
{
	//Init
	shared<Core> core = std::make_shared<Core>();
	core->Initialize();

	//Create a new entity
	shared<Entity> entity = core->addEntity();

	//Add a component
	auto entityRenderer = entity->addComponent<Renderer>();
	entityRenderer->onDisplay();

	//Start
	core->start();

	std::cout << "Dying" << std::endl;
	//getchar();
	return 0;
}
