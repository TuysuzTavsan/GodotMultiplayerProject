#include <librarian.h>

#include <enet/enet.h>
#include <iostream>

bool Librarian::Init()
{
    std::cout << "[Initializing libraries...]\n";

    int success = enet_initialize();

    if (success < 0)
    {
        std::cout << "[Error] Failed to initialize Enet library.\n";
        return success;
    }
    ENetVersion version = enet_linked_version();

    std::cout << "[Success] Initialized ENet library with version: " << version << "\n";

    return true;
}

void Librarian::DeInit()
{
    std::cout << "[DeInitializing libraries...]\n";
    enet_deinitialize();
}