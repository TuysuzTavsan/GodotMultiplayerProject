#include <locator.h>

void Locator::Init()
{
	m_parser = &m_nullParser;
	m_lobbyHandler = &m_nullLobbyHandler;
}


IParser& Locator::GetParser()
{
	return *m_parser;
}

void Locator::ProvideParser(IParser* parser)
{
	if (!parser)
	{
		//fall back to null service.
		m_parser = &m_nullParser;
	}
	else
	{
		m_parser = parser;
	}
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

NULLParser Locator::m_nullParser;
IParser* Locator::m_parser{ nullptr };

NULLLobbyHandler Locator::m_nullLobbyHandler;
ILobbyHandler* Locator::m_lobbyHandler{ nullptr };
