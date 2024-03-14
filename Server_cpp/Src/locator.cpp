#include <locator.h>

void Locator::Init()
{
	m_eventDistributor = &m_nullEventDistributor;
	m_lobbyHandler = &m_nullLobbyHandler;
	m_clientDistributor = &m_nullClientDistributor;
	m_packetDispatcher = &m_nullPacketDispatcher;
}

void Locator::ProvideEventDistributor(IEventDistributor* eventDistributor)
{
	if (!eventDistributor)
	{
		//fall back to null service.
		m_eventDistributor = &m_nullEventDistributor;
	}
	else
	{
		m_eventDistributor = eventDistributor;
	}
}

IEventDistributor& Locator::GetEventDistributor()
{
	return *m_eventDistributor;
}

void Locator::ProvideLobbyHandler(ILobbyHandler* lobbyHandler)
{
	if (!lobbyHandler)
	{
		//fall back to null service.
		m_lobbyHandler = &m_nullLobbyHandler;
	}
	else
	{
		m_lobbyHandler = lobbyHandler;
	}
}

ILobbyHandler& Locator::GetLobbyHandler()
{
	return *m_lobbyHandler;
}

void Locator::ProvideClientDistributor(IClientDistributor* clientDistributor)
{
	if (!clientDistributor)
	{
		//fall back to null service.
		m_clientDistributor = &m_nullClientDistributor;
	}
	else
	{
		m_clientDistributor = clientDistributor;
	}

}

IClientDistributor& Locator::GetClientDistributor()
{
	return *m_clientDistributor;
}

void Locator::ProvidePacketDispatcher(IPacketDispatcher* packetDispatcher)
{
	if (!packetDispatcher)
	{
		//fall back to null service.
		m_packetDispatcher = &m_nullPacketDispatcher;
	}
	else
	{
		m_packetDispatcher = packetDispatcher;
	}
}

IPacketDispatcher& Locator::GetPacketDispatcher()
{
	return *m_packetDispatcher;
}

NULLEventDistributor Locator::m_nullEventDistributor;
IEventDistributor* Locator::m_eventDistributor{ nullptr };

NULLLobbyHandler Locator::m_nullLobbyHandler;
ILobbyHandler* Locator::m_lobbyHandler{ nullptr };

NULLClientDistributor Locator::m_nullClientDistributor;
IClientDistributor* Locator::m_clientDistributor{ nullptr };

NULLPacketDispatcher Locator::m_nullPacketDispatcher;
IPacketDispatcher* Locator::m_packetDispatcher{ nullptr };
