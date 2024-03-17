#include <lobbyInfo.h>

LobbyInfo::LobbyInfo()
	:
	m_name{},
	m_capacity{ 0 },
	m_playerCount{ 0 },
	m_isSealed{ false }
{

}

LobbyInfo::~LobbyInfo()
{
	
}

LobbyInfo::LobbyInfo(const std::string& name, const std::uint8_t capacity,
	const std::uint8_t playerCount, bool isSealed)
	:
	m_name{ name },
	m_capacity{ capacity },
	m_playerCount{ playerCount },
	m_isSealed{ isSealed }
{

}

LobbyInfo::LobbyInfo(const LobbyInfo& other)
	:
	m_name{ other.m_name },
	m_capacity{ other.m_capacity },
	m_playerCount{ other.m_playerCount },
	m_isSealed{ other.m_isSealed }
{

}

LobbyInfo& LobbyInfo::operator=(const LobbyInfo& other)
{
	m_name = other.m_name;
	m_capacity = other.m_capacity;
	m_playerCount = other.m_playerCount;
	m_isSealed = other.m_isSealed;


	return *this;
}

LobbyInfo::LobbyInfo(LobbyInfo&& other)
	:
	m_name{ std::move(other.m_name) },
	m_capacity{ std::move(other.m_capacity) },
	m_playerCount{ std::move(other.m_playerCount) },
	m_isSealed{ std::move(other.m_isSealed) }
{

}


LobbyInfo& LobbyInfo::operator=(LobbyInfo&& other)
{
	m_name = std::move(other.m_name);
	m_capacity = std::move(other.m_capacity);
	m_playerCount = std::move(other.m_playerCount);
	m_isSealed = std::move(other.m_isSealed);

	return *this;
}