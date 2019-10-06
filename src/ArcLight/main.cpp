#include "../ArchitectEngine/dummy.h"

int main() {
    std::shared_ptr<dummy> dumbo(new dummy);

    dumbo->openWindow();
    std::cout << "Dying" << std::endl;
    //getchar();
    return 0;
}
