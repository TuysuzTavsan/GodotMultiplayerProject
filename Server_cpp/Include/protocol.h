#pragma once

#include <cstdint>

/*

FORMAT: {TopProtocol}{SubProtocol}{Actual Data}

*/

enum class TopProtocol
{
	Unspecified,
	Core,
	Lobby,
	Game,
	Physics
};

enum class CoreProt
{
	UserName
};

enum class LobbyProt
{
	LobbyEntered,
	LobbyLeft,
	LobbyCreated,
	LobbyOwnerChanged,
	LobbyMessageReceived,
	LobbyMessageSent
};

enum class GameProt
{

};

enum class PhysicsProt
{

};


struct Protocol
{
	TopProtocol m_topProt;
	std::uint8_t m_subProt;

	Protocol(const std::string& data)
		:
		m_topProt{TopProtocol::Unspecified},
		m_subProt{}
	{
		//This code will assume every message is received fully and lossless.
		
		m_topProt = static_cast<TopProtocol>(data[1] - '0');
		m_subProt = data[4] - '0';

	}


	~Protocol() = default;


};









/*

Core = Top protocol #06
UserName,
Activenes,
isFocused,



*/

/*

Lobby = Top protocol #1
LobbyMessageSubmit,-
LobbyMessageReceived,
LobbyEntered,
LobbyExit,


*/

/*


Game = Top protocol #2
GameStarted,
GameEnd,
PlayerKilled,
GameMsgReceived

*/