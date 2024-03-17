#pragma once

#include <client.h>
#include <lobbyInfo.h>

#include <map>
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
	Lobby(const std::string& name, const std::uint8_t& capacity);
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

	LobbyInfo GetInfo();

	std::string GetName();

private:

	void InsertClient(ClientID id);

	void EraseClient(ClientID id);

	std::map<ClientID, std::reference_wrapper<Client>> m_clients;
	std::string m_name;
	std::uint8_t m_capacity;
	bool m_isSealed;
};