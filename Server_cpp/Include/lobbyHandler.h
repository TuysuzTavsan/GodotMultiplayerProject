#pragma once

#include <unordered_map>
#include <iostream>
#include <string>

#include <lobby.h>
#include <protocol.h>
#include <ihandler.h>

/*
LobbyHandler is the top level class that will operate on lobbies. It has the ability to create and destroy lobbies.
Mostly it will operate with lobby helper functions rather then doing things itself.
This structure is thread safe?
*/

class ILobbyHandler : public IHandler
{
public:

	~ILobbyHandler() {}
};

class NULLLobbyHandler : public ILobbyHandler
{
public:

	void Input(const PacketIn& packet)  override;

private:

	void FreshClientAdded(const ClientInfo& info, const std::reference_wrapper<Client>& client) override;
	void ClientErased(const ClientInfo& info, const std::reference_wrapper<Client>& client) override;
	
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
	void Input(const PacketIn& packet) override;

private:
	
	void FreshClientAdded(const ClientInfo& info, const std::reference_wrapper<Client>& client) override;
	void ClientErased(const ClientInfo& info, const std::reference_wrapper<Client>& client) override;


	void CreateLobby(const std::string& name, const std::uint8_t& capacity);

	void EraseLobby(const LobbyID& id);

	static const LobbyID MAX_LOBBIES = 65535;
	std::unordered_map<LobbyID, class Lobby> m_lobbies;
	LobbyID m_counter;

};