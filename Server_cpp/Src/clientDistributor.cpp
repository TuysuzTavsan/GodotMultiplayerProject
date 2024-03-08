#include <clientDistributor.h>
#include <algorithm>
#include <stdexcept>

ClientDistributor::ClientDistributor()
{

}

ClientDistributor::~ClientDistributor()
{

}

void ClientDistributor::AddPeer(ENetPeer* peer)
{
	std::scoped_lock lk(m_mut);

	auto err = m_unhandledClients.emplace(std::make_pair(peer->connectID, Client(peer)));

	if (err.second == false)
	{
		throw std::exception("[EXCEPTION] Can not emplace peer to unordered map.");
	}

}

void ClientDistributor::AddPeer(Client& client, ClientID& id)
{
	std::scoped_lock lk(m_mut);

	auto err = m_unhandledClients.emplace(std::move(id), std::move(client));

	if (err.second == false)
	{
		throw std::exception("[EXCEPTION] Can not emplace peer to unordered map.");
	}
}

void ClientDistributor::RemoveDisconnectedPeer(ENetPeer* peer)
{
	std::scoped_lock lk(m_mut);



	auto err = std::erase_if(m_unhandledClients,
		[peer](auto& item) {return item.second.Get() == peer; }
	);

	if (err == 0) // Nothing is erased.
	{
		throw std::exception("[EXCEPTION] Can not erase peer from unordered map.");
	}

}

Client&& ClientDistributor::GetPeer(ClientID id)
{
	std::scoped_lock lk(m_mut);

	auto temp = m_unhandledClients.find(id);

	if (temp == m_unhandledClients.end()) //Cant find key.
	{
		throw std::exception("[EXCEPTION] Cant find peer by specified key.");
	}

	if (m_unhandledClients.erase(id) == 0) //1 if key value erased, and zero otherwise.
	{
		throw std::exception("[EXCEPTION] Can not erase peer from unordered map.");
	}


	return std::move(temp->second);

}