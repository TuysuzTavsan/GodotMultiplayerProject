#include <packetDispatcher.h>

PacketDispatcher::PacketDispatcher()
{

}

PacketDispatcher::~PacketDispatcher()
{
	
}

void PacketDispatcher::Dispatch()
{
	std::unique_lock lck(m_mut);
	m_cond.wait(lck,
		[this]() {return m_packetOut.size(); }
	);

	//TODO check the swap
	m_packetIn.swap(m_packetOut);

	lck.unlock();

	for (auto it = m_packetOut.begin(); it != m_packetOut.end();)
	{
		enet_peer_send(it->to, it->channel, it->packet);
		it = m_packetOut.erase(it);
	}

	
}

void PacketDispatcher::PutPacket(packetRequest packet)
{
	std::scoped_lock lck(m_mut);
	
	m_packetIn.push_back(packet);
}