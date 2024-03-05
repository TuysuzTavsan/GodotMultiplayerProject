#pragma once

#include <enet/enet.h>

#include <vector>
#include <mutex>
#include <condition_variable>


/*
Top level responsible class from dispatching packet requests.
This class will operate on its on thread.
Other threads may safely request sending packages as this class guarentees thread safety.
*/

//TODO Check if we are making another layer on top of ENetDispatch function.
//Which is pointless anyway.


struct packetRequest
{
	ENetPeer* to;
	ENetPacket* packet;
	std::uint8_t channel;
};

class PacketDispatcher
{
public:

	PacketDispatcher();
	~PacketDispatcher();
	
	//Copy constructor is not allowed.
	PacketDispatcher(const PacketDispatcher& other) = delete;

	//Copy assignment is not allowed.
	PacketDispatcher& operator=(const PacketDispatcher& other) = delete;

	void Dispatch();

	void PutPacket(packetRequest packet);


private:

	std::condition_variable m_cond;
	std::mutex m_mut;
	std::vector<packetRequest> m_packetIn; //Packets to store packets.
	std::vector<packetRequest> m_packetOut; //Packets to dispatch on next iteration.
};