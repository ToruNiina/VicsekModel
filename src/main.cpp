#include "System.hpp"

int main()
{
    vicsek::System system;
    system.init();
    system.run();
    return EXIT_SUCCESS;
}
