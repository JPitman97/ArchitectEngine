#include "../ArchitectEngine/Core.h"
#include <iostream>

#define shared std::shared_ptr
#define weak std::weak_ptr

int main()
{
	//Init
	shared<Core> core;
	core->Initialize();

	//Create a new entity
	shared<Entity> entity = core->addEntity();

	//Add a component TODO fix the circular dependency issue with this line!!!
	//entity->addComponent<Renderer>();

	//Start
	core->start();

	std::cout << "Dying" << std::endl;
	//getchar();
	return 0;
}
