#include <lobbyHandler.h>

#include <stdexcept>

#include <iostream>

LobbyHandler::LobbyHandler()
	:
	m_lobbies{},
	m_counter{0}
{

}

LobbyHandler::~LobbyHandler()
{

}

void LobbyHandler::CreateLobby()
{
	std::cout << "[SUCCESS] Created lobby!\n Total Lobbies:" << m_counter << " \n";

	if (m_counter == MAX_LOBBIES)
	{
		throw std::exception("[EXCEPTION] Reached max number of lobbies.");
	}
	
	auto err = m_lobbies.emplace(m_counter++, Lobby());

	if (!err.second) // will return true if insertion happened, otherwise false.
	{
		throw std::exception("[EXCEPTION] Trying to emplace already existing lobby.");
	}

}

void LobbyHandler::EraseLobby(const LobbyID& id)
{
	if (!m_lobbies.erase(id)) // will return 0 if nothing removed. 1 if removed.
	{
		throw std::exception("[EXCEPTION] Trying to erase unexisting lobby.");
	}
	//TODO handle counter for erasing
}

void LobbyHandler::InputMsg(Protocol protocol, std::unique_ptr<char>&& data)
{

	LobbyProt prot = static_cast<LobbyProt>(protocol.m_subProt);

	switch (prot)
	{
	case LobbyProt::LobbyEntered:
		break;
	case LobbyProt::LobbyLeft:
		break;
	case LobbyProt::LobbyCreated:
	
		CreateLobby();

		break;
	case LobbyProt::LobbyOwnerChanged:
		break;
	case LobbyProt::LobbyMessageReceived:
		break;
	case LobbyProt::LobbyMessageSent:
		break;
	default:
		break;
	}

}