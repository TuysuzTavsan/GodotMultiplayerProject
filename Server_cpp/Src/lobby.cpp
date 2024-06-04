#include <lobby.h>

#include <utility>
#include <locator.h>

Lobby::Lobby()
	:
	m_clients{},
	m_name{},
	m_capacity{0},
	m_isSealed{false}
{

}

Lobby::Lobby(const std::string& name, const std::uint8_t& capacity)
	:
	m_clients{},
	m_name{ name },
	m_capacity{capacity},
	m_isSealed{false}
{

}

Lobby::Lobby(Lobby&& other) noexcept
	:
	m_clients{std::move(other.m_clients)},
	m_name{std::move(other.m_name)},
	m_capacity{std::move(other.m_capacity)},
	m_isSealed{std::move(other.m_isSealed)}
{

}

Lobby::~Lobby()
{

}

Lobby& Lobby::operator=(Lobby&& other) noexcept
{

	m_clients = std::move(other.m_clients);
	m_name = std::move(other.m_name);
	m_capacity = std::move(other.m_capacity);
	m_isSealed = std::move(other.m_isSealed);

	return *this;
}

LobbyInfo Lobby::GetInfo()
{
	return LobbyInfo(m_name, m_capacity, m_clients.size(), m_isSealed);
}

std::string Lobby::GetName()
{
	return m_name;
}

void Lobby::InsertClient(ClientID id)
{
	if (m_clients.size() >= m_capacity)
	{
		throw std::logic_error("[EXCEPTION] Lobby max capacity already reached.");
	}

	Client& client = Locator::GetClientDistributor().GetClient(id);

	auto err = m_clients.emplace(id, std::ref(client));

	if (!err.second) // will return true if insertion happened, otherwise false.
	{
		throw std::logic_error("[EXCEPTION] Trying to emplace already existing peer to lobby.");
	}

}

void Lobby::EraseClient(ClientID id)
{
	if (!m_clients.erase(id)) // will return 0 if nothing removed. 1 if removed.
	{
		throw std::logic_error("[EXCEPTION] Trying to erase non existing client from lobby.");
	}

}


