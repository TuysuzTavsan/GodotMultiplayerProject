#pragma once

#include <string>
#include <cstdint>

/*
Helper struct to hold lobby related information to send over client.
This struct is copyable and moveable.
This struct is not thread safe.
*/

struct LobbyInfo
{
	LobbyInfo();
	LobbyInfo(const std::string& name, const std::uint8_t capacity,
		const std::uint8_t playerCount, bool isSealed);
	~LobbyInfo();

	//Copy constructor
	LobbyInfo(const LobbyInfo& other);

	//Copy assignment operator
	LobbyInfo& operator=(const LobbyInfo& other);

	//Move constructor
	LobbyInfo(LobbyInfo&& other);

	//Move assignment operator
	LobbyInfo& operator=(LobbyInfo&& other);

	std::string m_name;
	std::uint8_t m_capacity;
	std::uint8_t m_playerCount;
	bool m_isSealed;
};
