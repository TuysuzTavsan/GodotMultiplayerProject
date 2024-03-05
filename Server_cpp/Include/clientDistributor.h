#pragma once

#include <vector>
#include <unordered_map>
#include <enet/enet.h>
#include <mutex>
#include <condition_variable>


enum DistributeID
{
	Unhandled,
	Lobby,
	Game
};


//Simple struct to work with peer distribution.
struct DistributedPeer
{
	ENetPeer* m_peer; //ENetPeer object.
	DistributeID m_handler; //Enum which indicates this peers handler.

	DistributedPeer():
		m_peer{nullptr},
		m_handler{DistributeID::Unhandled}
	{}

	DistributedPeer(ENetPeer* peer, DistributeID id)
		:
		m_peer(peer),
		m_handler(id)
	{}
};

/*
Responsible from distributing clients to network pipeline.
Example: Every new client connection will be distributed to the lobbyHandler.
Every client that is playing a game session will be distributed to the GameHandler.
Every call to this class is blocking. (protected by a mutex.)
*/
class ClientDistributor {
public:

	ClientDistributor();
	~ClientDistributor();

	//Call this method whenever new connection is established.
	void AddFreshPeer(ENetPeer* peer);

	//Remove a disconnected peer.
	void RemoveDisconnectedPeer(ENetPeer* peer);

	//Update method will wait on a mutex, mutex will be only unlocked when there is work to do.
	void Update();

	//Get peer by ID.
	//TODO

	//Request to change peer handler.
	void Request(ENetPeer* peer, DistributeID id);

private:

	//Find the peer and get its key.
	//void FindPeer(ENetPeer* peer);

	std::vector<ENetPeer*> m_unhandledPeers; //vector of peers that are not handled yet.
	std::unordered_map<ENetPeer*, DistributeID> m_distributedPeers; //Map of peers that are already distributed.
	std::vector<DistributedPeer> m_requests; //Vector of requests.
	std::condition_variable m_cond; //Condition which indicates peer distribution is needed.
	std::mutex m_mut;
	bool m_shouldWork = false;
};