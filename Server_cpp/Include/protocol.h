#pragma once

#include <cstdint>
#include <handlerID.h>
#include <string>

/*

FORMAT: {TopProtocol}{SubProtocol}{Data}

TopProtocol will be used by the Parser to forward incoming packets.
SubProtocol is meant to be used by the packet consumer class, example LobbyHandler.

*/

namespace prot
{
	enum class Top
	{
		Unspecified,
		Distribute,
		Lobby,
	};

	enum class Lobby
	{
		LobbyCreated
	};

	using Distribute = HandlerID;
}


//Helper class to solve protocol of incoming packets.
struct Protocol
{
	prot::Top m_topProt;
	std::uint8_t m_subProt;

	Protocol()
		:
		m_topProt{ prot::Top::Unspecified },
		m_subProt{ 0 }
	{

	}

	Protocol(const std::string& data)
		:
		m_topProt{prot::Top::Unspecified},
		m_subProt{}
	{
		//This code will assume every message is received fully and lossless.
		
		m_topProt = static_cast<prot::Top>(data[1] - '0');
		m_subProt = data[4] - '0';

	}

	void Set(const std::string& data)
	{
		m_topProt = static_cast<prot::Top>(data[1] - '0');
		m_subProt = data[4] - '0';
	}


	~Protocol() = default;


};
