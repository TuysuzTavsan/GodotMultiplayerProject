#include <lobby.h>

#include <utility>

Lobby::Lobby()
	:
	m_clients{},
	m_name{}
{

}

Lobby::Lobby(const std::string& name)
	:
	m_clients{},
	m_name{ name }
{

}

Lobby::Lobby(Lobby&& other) noexcept
	:
	m_clients{std::move(other.m_clients)},
	m_name{std::move(other.m_name)}
{

}

Lobby::~Lobby()
{

}

Lobby& Lobby::operator=(Lobby&& other) noexcept
{

	m_clients = std::move(other.m_clients);
	m_name = std::move(other.m_name);

	return *this;
}

std::string Lobby::GetName()
{
	return m_name;
}

void Lobby::InsertClient(ClientID id)
{
	//ClientDistributor::GetClient
	Client client(nullptr);
	//TODO

	auto err = m_clients.emplace(id, std::move(client));

	if (!err.second) // will return true if insertion happened, otherwise false.
	{
		throw std::exception("[EXCEPTION] Trying to emplace already existing peer to lobby.");
	}

}

void Lobby::EraseClient(ClientID id)
{
	if (!m_clients.erase(id)) // will return 0 if nothing removed. 1 if removed.
	{
		throw std::exception("[EXCEPTION] Trying to erase non existing client from lobby.");
	}

}


