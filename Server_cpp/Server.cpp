#include <iostream>
#include <enet/enet.h>

int main()
{
    int success = enet_initialize();
    if (success < 0)
    {
        std::cout << "Failed to initialize Enet.";
        return -1;
    }

    enet_deinitialize();


    std::cout << "Hello World!\n";
}
