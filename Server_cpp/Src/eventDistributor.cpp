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

	case prot::Top::Distribute:
		{
			Locator::GetClientDistributor().ReDistributePeer(packet.m_id, static_cast<HandlerID>(packet.m_prot.m_subProt));

			break;
		}

	case prot::Top::Lobby:
		
		//Do this with IHandler and HandlerHelper to achieve complete interface feeling.
		//Locator::GetLobbyHandler().InputMsg(_protocol, std::move(data));

		break;
		
	}
}