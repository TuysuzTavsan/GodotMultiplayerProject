#pragma once

#include <unordered_map>
#include <lobby.h>
#include <protocol.h>
#include <memory>

/*
LobbyHandler is the top level class that will operate on lobbies. It has the ability to create and destroy lobbies.
Mostly it will operate with lobby helper functions rather then doing things itself.
This structure is thread safe?
*/

class ILobbyHandler
{
public:

	~ILobbyHandler() {}

	virtual void InputMsg(Protocol protocol, std::unique_ptr<char>&& data) = 0;
};

class NULLLobbyHandler : public ILobbyHandler
{
public:

	void InputMsg(Protocol protocol, std::unique_ptr<char>&& data) override
	{
		//do nothing.
	}
};

class LobbyHandler : public ILobbyHandler
{
public:

	LobbyHandler();
	~LobbyHandler();

	//Move constructor is prohibited.
	LobbyHandler(const LobbyHandler& other) = delete;

	//Move assignment operator is prohibited.
	LobbyHandler& operator=(const LobbyHandler& other) = delete;

	//Forwarding msg from external source needs public method here.
	void InputMsg(Protocol protocol, std::unique_ptr<char>&& data) override;

private:

	void CreateLobby();

	void EraseLobby(const LobbyID& id);

	static const LobbyID MAX_LOBBIES = 65535;
	std::unordered_map<LobbyID, class Lobby> m_lobbies;
	LobbyID m_counter;

};