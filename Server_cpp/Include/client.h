#pragma once

#include <enet/enet.h>

#include <cstdint>
#include <string>

/*
Client is just a wrapper around ENetPeer*.
Copy is prohibited.
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
	
	bool operator==(const Client& other) const;

	//Send packet.
	void Send(const std::string& msg, const std::uint8_t& channel, const ENetPacketFlag& flag);

	ENetPeer* Get();


	void SetUserName(const std::string& name);

	std::string GetName();

private:

	ENetPeer* m_peer;
	std::string m_userName;

};