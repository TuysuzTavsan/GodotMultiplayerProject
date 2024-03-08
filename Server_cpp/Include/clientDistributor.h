#pragma once

#include <unordered_map>
#include <mutex>

#include <enet/enet.h>

#include <client.h>

/*
Responsible from distributing clients to network pipeline.
Example: Every new client connection will be distributed to the lobbyHandler.
Every client that is playing a game session will be distributed to the GameHandler's ownership.
Every client that just entered lobby will be distributed to the lobby's ownership.
Every call to this class is blocking. (protected by a mutex.)
*/

class ClientDistributor {
public:

	ClientDistributor();
	~ClientDistributor();

	//Call this method whenever new connection is established.
	void AddPeer(ENetPeer* peer);

	void AddPeer(Client& client, ClientID& id);

	//Remove a disconnected peer.
	void RemoveDisconnectedPeer(ENetPeer* id);

	Client&& GetPeer(ClientID id);

	//Get peer by ID.
	//TODO

private:

	//Find the peer and get its key.
	// 
	//void FindPeer(ENetPeer* peer);

	std::mutex m_mut;
	std::unordered_map<ClientID, class Client> m_unhandledClients; //vector of peers that are not handled yet.	std::mutex m_mut;
};