#include <host.h>
#include <servInfo.h>
#include <iostream>


Host::Host()
{
    /* Create host connection. */

    std::cout << "[Creating host...]\n";

    m_address.host = ENET_HOST_ANY;
    m_address.port = servinfo::PORT;

    m_server = enet_host_create(&m_address          /* the address to bind the server host to */,
        servinfo::MAX_CLIENTS                       /* allow up to 32 clients and/or outgoing connections */,
        servinfo::CHANNELS                          /* allow up to 2 channels to be used, 0 and 1 */,
        0                                           /* assume any amount of incoming bandwidth */,
        0                                           /* assume any amount of outgoing bandwidth */);

    //check if succesfully created host.
    if (m_server == NULL)
    {
        std::cout << "[ERROR] Failed to create host on Port: " << (unsigned)servinfo::PORT << "\n";
        throw std::exception("Failed to create host.");
    }

    //log success.
    std::cout << "[Success] Host created on Port: " << (unsigned)servinfo::PORT << " with MaxClientCount: " 
        << (unsigned)servinfo::MAX_CLIENTS << " with " << (unsigned)servinfo::CHANNELS << " channels.\n";
}

Host::~Host()
{
    //log and destroy host.
    std::cout << "[Destroying host...]\n";
    enet_host_destroy(m_server);
}