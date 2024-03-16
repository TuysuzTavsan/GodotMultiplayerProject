#pragma once

#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>

#include <packet.h>

/*
Top level responsible class from dispatching packet requests.
This class will operate on its on thread.
Other threads may safely request sending packages as this class guarentees thread safety.
*/
class IPacketDispatcher
{
public:
	IPacketDispatcher() = default;
	virtual ~IPacketDispatcher() = default;

	virtual void Dispatch() = 0;
	virtual void PutPacket(PacketOut& packet) = 0;
	virtual void PutPacket(PacketOut&& packet) = 0;
};

class NULLPacketDispatcher : public IPacketDispatcher
{
public:
	NULLPacketDispatcher() = default;
	~NULLPacketDispatcher() = default;

	void Dispatch() override
	{
		std::cout << "[NULLPacketDispatcher is provided]\n";
	}

	void PutPacket(PacketOut& packet) override
	{
		std::cout << "[NULLPacketDispatcher is provided]\n";
	}

	void PutPacket(PacketOut&& packet) override
	{
		std::cout << "[NULLPacketDispatcher is provided]\n";
	}
};

class PacketDispatcher : public IPacketDispatcher
{
public:

	PacketDispatcher();
	~PacketDispatcher();
	
	//Copy constructor is not allowed.
	PacketDispatcher(const PacketDispatcher& other) = delete;

	//Copy assignment is not allowed.
	PacketDispatcher& operator=(const PacketDispatcher& other) = delete;

	//Will dispatch packets in its own thread.
	void Dispatch() override;

	//Put packet to dispatch on the next iteration.
	void PutPacket(PacketOut& packet) override;

	//Put packet to dispatch on the next iteration.
	void PutPacket(PacketOut&& packet) override;

	void Terminate();


private:

	std::condition_variable m_cond;
	std::mutex m_mut;
	std::vector<PacketOut> m_packetIn; //Packets to store packets.
	std::vector<PacketOut> m_packetOut; //Packets to dispatch on next iteration.
	bool m_shouldRun;
};