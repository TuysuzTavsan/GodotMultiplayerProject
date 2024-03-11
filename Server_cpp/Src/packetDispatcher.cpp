#include <packetDispatcher.h>

#include <iostream>

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
		if (it->Send() == 0)
		{
			std::cout << "Successfully sended packet.\n";
		}
		it = m_packetOut.erase(it);
	}

	
}

void PacketDispatcher::PutPacket(PacketOut& packet)
{
	std::scoped_lock lck(m_mut);
	
	m_packetIn.push_back(std::move(packet));
}

void PacketDispatcher::PutPacket(PacketOut&& packet)
{
	std::scoped_lock lck(m_mut);

	m_packetIn.push_back(std::move(packet));
}