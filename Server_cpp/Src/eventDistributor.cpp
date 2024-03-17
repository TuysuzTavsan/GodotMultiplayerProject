#include <eventDistributor.h>

#include <iostream>
#include <packet.h>
#include <locator.h>

/* Section NULLParser starts */

void NULLEventDistributor::Handle(const ENetEvent& event)
{
	/*Do nothing*/
	std::cout << "[NULLParser is Provided]\n";
}

/* Section NULLParser ends */

EventDistributor::EventDistributor()
{

}

EventDistributor::~EventDistributor()
{

}

void EventDistributor::Handle(const ENetEvent& event)
{
	PacketIn packet(event.peer, event.peer->connectID, event.packet->data, event.packet->dataLength, event.channelID);

	switch (packet.m_prot.m_topProt)
	{
	case prot::Top::User:
		{

			//TODO UserManager class.
			Client& client = Locator::GetClientDistributor().GetClient(event.peer->connectID);
			client.SetUserName(packet.m_data);
			std::cout << "User Name Set called. " << packet.m_data << "\n";

			Protocol prot(prot::Top::User, static_cast<std::uint8_t>(prot::User::UserNameSubmit));
			PacketOut out(event.peer, prot, client.GetName(), ENetPacketFlag::ENET_PACKET_FLAG_RELIABLE, 0);
			Locator::GetPacketDispatcher().PutPacket(out);

			break;
		}
	case prot::Top::Distribute:
		{
			Locator::GetClientDistributor().ReDistributePeer(packet.m_id, static_cast<HandlerID>(packet.m_prot.m_subProt));

			break;
		}

	case prot::Top::Lobby:
		
		Locator::GetLobbyHandler().Input(std::move(packet));

		break;
		
	}
}