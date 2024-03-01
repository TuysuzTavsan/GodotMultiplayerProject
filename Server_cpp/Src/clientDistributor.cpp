#include <clientDistributor.h>
#include <algorithm>

ClientDistributor::ClientDistributor()
{

}

ClientDistributor::~ClientDistributor()
{

}

void ClientDistributor::AddFreshPeer(ENetPeer* peer)
{
	std::scoped_lock lk(m_mut);
	m_unhandledPeers.push_back(peer);
	m_shouldWork = true;

}

void ClientDistributor::RemoveDisconnectedPeer(ENetPeer* peer)
{
	std::scoped_lock lk(m_mut);

	//erase if its from unhandledpeers.
	m_unhandledPeers.erase(std::remove_if(m_unhandledPeers.begin(), m_unhandledPeers.end(),
		[peer](ENetPeer* _peer) {return _peer == peer; }
		),
		m_unhandledPeers.end()
	);

	//erase if its from distributedpeers.
	m_distributedPeers.erase(peer);

}

void ClientDistributor::Request(ENetPeer* peer, DistributeID id)
{
	std::scoped_lock lk(m_mut);

	m_requests.emplace_back(DistributedPeer(peer, id));

}

void ClientDistributor::Update()
{
	
}