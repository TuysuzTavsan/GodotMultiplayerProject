#include <iostream>
#include <cstdint>
#include <servInfo.h>
#include <enet/enet.h>


int main33()
{
    using namespace servinfo;
    int success = enet_initialize();
    if (success < 0)
    {
        std::cout << "Failed to initialize Enet.";
        return success;
    }
    ENetVersion version = enet_linked_version();


    /*
    Create host connection.
    */
    ENetAddress address;
    ENetHost* server;

    address.host = ENET_HOST_ANY;
    address.port = PORT;

    server = enet_host_create(&address  /* the address to bind the server host to */,
        MAX_CLIENTS                     /* allow up to 32 clients and/or outgoing connections */,
        CHANNELS                        /* allow up to 2 channels to be used, 0 and 1 */,
        0                               /* assume any amount of incoming bandwidth */,
        0                               /* assume any amount of outgoing bandwidth */);
    
    if (server == NULL)
    {
        std::cout << "[ERROR] Failed to create server on Port " << PORT << "\n";
        return -1;
    }


    /*
    Poll events.
    */

    ENetEvent _event;

poll:
    while (enet_host_service(server, &_event, 1000) > 0) //Will return 1 if any events dispatched.
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

    std::cout << "[Polling] No event received. Looping...\n";

    goto poll;


    
    std::cout << "[INFO] Enet initialized succesfully. [Enet Version " << version << "]\n";
    std::cout << "[INFO] Succesfully created server on Port " << PORT << " with " << unsigned(CHANNELS) << ".\n";



    enet_deinitialize();
}
