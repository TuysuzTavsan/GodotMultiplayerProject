#pragma once

#include <unordered_map>
#include <lobby.h>

/*
LobbyHandler is the top level class that will operate on lobbies. It has the ability to create and destroy lobbies.
Mostly it will operate with lobby helper functions rather then doing things itself.
This structure is thread safe?
*/

class LobbyHandler
{
public:

	LobbyHandler();
	~LobbyHandler();

	//Move constructor is prohibited.
	LobbyHandler(const LobbyHandler& other) = delete;

	//Move assignment operator is prohibited.
	LobbyHandler& operator=(const LobbyHandler& other) = delete;

	//Forwarding msg from external source needs public method here.
	void InputMsg();

private:

	void CreateLobby();

	void EraseLobby(const LobbyID& id);

	static const LobbyID MAX_LOBBIES = 65535;
	std::unordered_map<LobbyID, class Lobby> m_lobbies;
	LobbyID m_counter;

};