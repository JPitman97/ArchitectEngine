#include "../ArchitectEngine/Core.h"
#include <iostream>

#define shared std::shared_ptr
#define weak std::weak_ptr

int main()
{
	//Init
	shared<Core> core = Core::Initialize();

	//Create a new entity
	shared<Entity> entity = core->addEntity();

	//Add a component
	

	//Start
	core->start();

	std::cout << "Dying" << std::endl;
	//getchar();
	return 0;
}
