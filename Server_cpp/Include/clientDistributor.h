#pragma once

#include <map>
#include <mutex>

#include <enet/enet.h>

#include <client.h>
#include <clientInfo.h>
#include <iostream>

/*
Responsible from distributing clients to handlers via IHandler interface and HandlerHelper static class.
Every call to this class is blocking. (protected by a mutex.)
This class is thread safe.
*/

class IClientDistributor
{
public:

	IClientDistributor() = default;
	virtual ~IClientDistributor() = default;

	virtual void AddFreshPeer(ENetPeer* peer) = 0;
	virtual void ReDistributePeer(ClientID& id, HandlerID& handlerID) = 0;
	virtual void ReDistributePeer(ClientID& id, HandlerID&& handlerID) = 0;
	virtual ClientID RemoveDisconnectedPeer(ENetPeer* id) = 0;
	virtual Client& GetClient(const ClientID& id) = 0;

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

	ClientID RemoveDisconnectedPeer(ENetPeer* id) override
	{
		std::cout << "[NULLClientDistributor provided]\n";
		return 0;
	}

	Client& GetClient(const ClientID& id) override
	{
		std::cout << "[NULLClientDistributor provided]\n";
	
		Client* temp = nullptr;

		//TODO fix nullptr
		return *temp;
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
	ClientID RemoveDisconnectedPeer(ENetPeer* id) override;

	//TODO CHANGE THIS
	Client& GetClient(const ClientID& id) override;

private:

	std::mutex m_mut;
	std::map<ClientInfo, Client> m_clients; // map of peers that are unhandled at the moment.
};