#include <locator.h>

void Locator::Init()
{
	m_eventDistributor = &m_nullEventDistributor;
	m_lobbyHandler = &m_nullLobbyHandler;
	m_clientDistributor = &m_nullClientDistributor;
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

NULLEventDistributor Locator::m_nullEventDistributor;
IEventDistributor* Locator::m_eventDistributor{ nullptr };

NULLLobbyHandler Locator::m_nullLobbyHandler;
ILobbyHandler* Locator::m_lobbyHandler{ nullptr };

NULLClientDistributor Locator::m_nullClientDistributor;
IClientDistributor* Locator::m_clientDistributor{ nullptr };
