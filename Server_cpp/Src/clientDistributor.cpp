#include <clientDistributor.h>
#include <handlerHelper.h>
#include <algorithm>
#include <stdexcept>

ClientDistributor::ClientDistributor()
{

}

ClientDistributor::~ClientDistributor()
{

}

void ClientDistributor::AddFreshPeer(ENetPeer* peer)
{
	std::scoped_lock lk(m_mut);

	auto err = m_clients.emplace(peer->connectID, peer);

	if (err.second == false)
	{
		throw std::exception("[EXCEPTION] Can not emplace fresh peer to unordered map.");
	}

}

void ClientDistributor::ReDistributePeer(ClientID& id, HandlerID& handlerID)
{
	std::scoped_lock lk(m_mut);

	auto it = std::find_if(m_clients.begin(), m_clients.end(),
		[&id](const auto& pair) {return pair.first.m_clientID == id; }
	);

	if (it == m_clients.end())
	{
		//Couldnt find
		throw std::exception("[EXCEPTION] Can not find peer to redistribute.");
	}

	if (it->first.m_handlerID == handlerID)
	{
		//Already there.
		throw std::exception("[EXCEPTION] Client already distributed to desired Handler.");
	}

	//Extract, update key, emplace.
	auto node = m_clients.extract(it);
	//Change member of the key.
	node.key().m_handlerID = handlerID;
	//reinsert
	auto err = m_clients.insert(std::move(node));

	if (!err.inserted) 
	{
		//emplace did not happen.
		throw std::exception("[EXCEPTION] Can not emplace redistributed peer.");
	}

	auto handler = HandlerHelper::GetSubscriber(handlerID);
	handler.get().AddClient(std::ref(err.node.mapped()));

}

void ClientDistributor::ReDistributePeer(ClientID& id, HandlerID&& handlerID)
{
	std::scoped_lock lk(m_mut);

	auto it = std::find_if(m_clients.begin(), m_clients.end(),
		[&id](const auto& pair) {return pair.first.m_clientID == id; }
	);

	if (it == m_clients.end())
	{
		//Couldnt find
		throw std::exception("[EXCEPTION] Can not find peer to redistribute.");
	}

	if (it->first.m_handlerID == handlerID)
	{
		//Already there.
		throw std::exception("[EXCEPTION] Client already distributed to desired Handler.");
	}

	//Extract, update key, emplace.
	auto node = m_clients.extract(it);
	//Change member of the key.
	node.key().m_handlerID = handlerID;
	//reinsert
	auto err = m_clients.insert(std::move(node));

	if (!err.inserted)
	{
		//emplace did not happen.
		throw std::exception("[EXCEPTION] Can not emplace redistributed peer.");
	}

	auto handler = HandlerHelper::GetSubscriber(handlerID);
	handler.get().AddClient(std::ref(err.node.mapped()));

}

void ClientDistributor::RemoveDisconnectedPeer(ENetPeer* peer)
{
	std::scoped_lock lk(m_mut);

	auto err = std::erase_if(m_clients,
		[peer](auto& item) {return item.second.Get() == peer; }
	);

	if (err == 0) // Nothing is erased.
	{
		throw std::exception("[EXCEPTION] Can not erase peer from unordered map.");
	}

}