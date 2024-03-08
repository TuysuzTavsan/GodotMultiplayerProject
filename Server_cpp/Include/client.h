#pragma once

#include <enet/enet.h>

#include <cstdint>
#include <string>

/*
Clients are structures build on top of ENetPeer.
It halso holds all related information about a client.
*/

typedef std::uint32_t ClientID;

class Client
{
public:

	explicit Client(ENetPeer* peer);
	~Client();

	//Move constructor
	Client(Client&& other) noexcept;

	//Move assignment
	Client& operator=(Client&& other) noexcept;

	//Copy constructor is prohibited.
	Client(const Client& other) = delete;

	//Copy assignment operator is prohibited.
	Client& operator=(const Client& other) = delete;
	

	//Send_msg
	void Send(const std::string& msg, std::uint8_t channel, const ENetPacketFlag& flag);

	ENetPeer* Get();


private:

	ENetPeer* m_peer;

};