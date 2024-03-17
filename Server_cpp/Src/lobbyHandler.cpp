#include <lobbyHandler.h>

#include <locator.h>

#include <stdexcept>
#include <iostream>


void NULLLobbyHandler::Input(const PacketIn& packet)
{
	std::cout << "[NULLLobbyHandler is provided]\n";
}

void NULLLobbyHandler::FreshClientAdded(const ClientInfo& info, const std::reference_wrapper<Client>& client)
{
	std::cout << "[NULLLobbyHandler is provided]\n";
}

void NULLLobbyHandler::ClientErased(const ClientInfo& info, const std::reference_wrapper<Client>& client)
{
	std::cout << "[NULLLobbyHandler is provided]\n";
}







LobbyHandler::LobbyHandler()
	:
	m_lobbies{},
	m_counter{0}
{
	this->SetID(HandlerID::lobby);
}

LobbyHandler::~LobbyHandler()
{

}

void LobbyHandler::CreateLobby(const std::string& name, const std::uint8_t& capacity)
{
	

	if (m_counter == MAX_LOBBIES)
	{
		throw std::exception("[EXCEPTION] Reached max number of lobbies.");
	}
	
	auto err = m_lobbies.emplace(m_counter++, Lobby(name, capacity));

	if (!err.second) // will return true if insertion happened, otherwise false.
	{
		throw std::exception("[EXCEPTION] Trying to emplace already existing lobby.");
	}

	std::cout << "[SUCCESS] Created lobby!\n Total Lobbies:" << m_counter << " \n";

}

void LobbyHandler::EraseLobby(const LobbyID& id)
{
	if (!m_lobbies.erase(id)) // will return 0 if nothing removed. 1 if removed.
	{
		throw std::exception("[EXCEPTION] Trying to erase unexisting lobby.");
	}
	//TODO handle counter for erasing
}

void LobbyHandler::Input(const PacketIn& packet)
{
	switch (static_cast<prot::Lobby>(packet.m_prot.m_subProt))
	{
	case prot::Lobby::LobbyCreated:
	{
		//{name}{capacity}

		int size = packet.m_data.size();
		int nameEndPos = packet.m_data.find_first_of('}', 0);

		std::string lobbyName = packet.m_data.substr(1, nameEndPos - 1);
		
		int capacity = packet.m_data[nameEndPos + 2] - '0';


		CreateLobby(lobbyName, capacity);
		break;
	}
	case prot::Lobby::LobbyJoin:
	{

		break;
	}
	case prot::Lobby::LobbyLeft:
	{

		break;
	}
	case prot::Lobby::LobbyList:
	{
		Protocol prot(prot::Top::Lobby, static_cast<uint8_t>(prot::Lobby::LobbyList));

		std::string data;

		for (auto it = m_lobbies.begin(); it != m_lobbies.end(); it++)
		{
			LobbyInfo info = it->second.GetInfo();

			data += "{";
			data += info.m_name;
			data += "}";
			
			data += "{";
			data += (char)info.m_playerCount + '0';
			data += "}";

			data += "{";
			data += (char)info.m_capacity + '0';
			data += "}";

			data += "{";
			data += (char)info.m_isSealed + '0';
			data += "}";
		}

		PacketOut tempPacket(packet.m_owner, prot, data, ENET_PACKET_FLAG_RELIABLE, 0);
		Locator::GetPacketDispatcher().PutPacket(tempPacket);

		break;
	}
	}
	
}

void LobbyHandler::FreshClientAdded(const ClientInfo& info, const std::reference_wrapper<Client>& client)
{
	Protocol prot(prot::Top::Distribute, static_cast<std::uint8_t>(prot::Distribute::lobby));
	PacketOut out(client.get().Get(), prot, "", ENetPacketFlag::ENET_PACKET_FLAG_RELIABLE, 0);
	Locator::GetPacketDispatcher().PutPacket(out);
}

void LobbyHandler::ClientErased(const ClientInfo& info, const std::reference_wrapper<Client>& client)
{

}