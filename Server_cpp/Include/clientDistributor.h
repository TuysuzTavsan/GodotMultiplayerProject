#pragma once

#include <map>
#include <mutex>

#include <enet/enet.h>

#include <client.h>
#include <clientInfo.h>
#include <iostream>

/*
Responsible from distributing clients to network pipeline.
Example: Every new client connection will be distributed to the lobbyHandler.
Every client that is playing a game session will be distributed to the GameHandler's ownership.
Every client that just entered lobby will be distributed to the lobby's ownership.
Every call to this class is blocking. (protected by a mutex.)
*/

class IClientDistributor
{
public:

	IClientDistributor() = default;
	virtual ~IClientDistributor() = default;

	virtual void AddFreshPeer(ENetPeer* peer) = 0;
	virtual void ReDistributePeer(ClientID& id, HandlerID& handlerID) = 0;
	virtual void ReDistributePeer(ClientID& id, HandlerID&& handlerID) = 0;
	virtual void RemoveDisconnectedPeer(ENetPeer* id) = 0;

};

class NULLClientDistributor : public IClientDistributor
{
public:

	NULLClientDistributor() = default;
	~NULLClientDistributor() = default;

	void AddFreshPeer(ENetPeer* peer) override
	{
		std::cout << "[NULLClientDistributor provided]\n";
	}

	void ReDistributePeer(ClientID& id, HandlerID& handlerID) override
	{
		std::cout << "[NULLClientDistributor provided]\n";
	}

	//Call this method to redistribute client.
	void ReDistributePeer(ClientID& id, HandlerID&& handlerID) override
	{
		std::cout << "[NULLClientDistributor provided]\n";
	}

	void RemoveDisconnectedPeer(ENetPeer* id) override
	{
		std::cout << "[NULLClientDistributor provided]\n";
	}
};


class ClientDistributor : public IClientDistributor
{
public:

	ClientDistributor();
	~ClientDistributor();

	//Call this method whenever new connection is established.
	void AddFreshPeer(ENetPeer* peer) override;

	//Call this method to redistribute client.
	void ReDistributePeer(ClientID& id, HandlerID& handlerID) override;

	//Call this method to redistribute client.
	void ReDistributePeer(ClientID& id, HandlerID&& handlerID) override;

	//Remove a disconnected peer.
	void RemoveDisconnectedPeer(ENetPeer* id) override;

	//Get peer

private:

	std::mutex m_mut;
	std::map<ClientInfo, Client> m_clients; // map of peers that are unhandled at the moment.
};