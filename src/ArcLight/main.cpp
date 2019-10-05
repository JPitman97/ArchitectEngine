#include "dummy.h"

int main()
{
	std::shared_ptr<dummy> dumbo(new dummy);

	dumbo->openWindow();

	getchar();
	return 0;
}
