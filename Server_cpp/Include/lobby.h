#pragma once

#include <client.h>

#include <unordered_map>
#include <cstdint>
#include <string>



//Type alias to set ID of a lobby.
typedef std::uint16_t LobbyID;

/*
Lobby is a container with some helper functions to deal with lobby management.
This structure is not thread safe.
*/
class Lobby
{
public:

	Lobby();
	Lobby(const std::string& name);
	~Lobby();
	
	//Move constructor.
	Lobby(Lobby&& other) noexcept;

	//Move assignment.
	Lobby& operator=(Lobby&& other) noexcept;

	//Copy constructor is prohibited.
	Lobby(const Lobby& other) = delete;
	
	//Copy assignment is prohibited.
	Lobby& operator=(const Lobby& other) = delete;

	//Public method for handling lobby specific processes.
	void HandleMsg();

	std::string GetName();

private:

	void InsertClient(ClientID id);

	void EraseClient(ClientID id);

	std::unordered_map<ClientID, Client> m_clients;
	std::string m_name;
};