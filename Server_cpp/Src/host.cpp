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

    //check if successfully created host.
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

void Host::PollEvents()
{
    ENetEvent _event;
    /* Wait and dispatch all events. */
    std::cout << "[Polling...]\n";
    while (enet_host_service(m_server, &_event, servinfo::POLLINTERVAL) > 0)
    {
        switch (_event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            printf("A new client connected from %x:%u.\n",
                _event.peer->address.host,
                _event.peer->address.port);
            /* Store any relevant client information here. */
            _event.peer->data = reinterpret_cast<void*>(*"Client information");
            continue;

        case ENET_EVENT_TYPE_RECEIVE:
            printf("A packet of length %zu containing %s was received from %s on channel %u.\n",
                (_event.packet->dataLength),
                (_event.packet->data),
                reinterpret_cast<char*>(_event.peer->data),
                _event.channelID);
            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy(_event.packet);
            continue;

        case ENET_EVENT_TYPE_DISCONNECT:

            std::cout << _event.peer->connectID << " disconnected.\n";
            /* Reset the peer's client information. */
            _event.peer->data = NULL;
            continue;
        }
    }
}