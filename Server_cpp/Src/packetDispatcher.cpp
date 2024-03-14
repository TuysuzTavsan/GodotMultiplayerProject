#include <packetDispatcher.h>

#include <iostream>

PacketDispatcher::PacketDispatcher()
	:
	m_shouldRun{true}
{

}

PacketDispatcher::~PacketDispatcher()
{
	
}

void PacketDispatcher::Dispatch()
{
	while (m_shouldRun)
	{
		std::unique_lock lck(m_mut);
		m_cond.wait(lck);
		if (!m_packetIn.size())
		{
			continue;
		}

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
	

	
}

void PacketDispatcher::PutPacket(PacketOut& packet)
{
	std::scoped_lock lck(m_mut);
	
	m_packetIn.push_back(std::move(packet));
	m_cond.notify_one();
}

void PacketDispatcher::PutPacket(PacketOut&& packet)
{
	std::scoped_lock lck(m_mut);

	m_packetIn.push_back(std::move(packet));
	m_cond.notify_one();
}

void PacketDispatcher::Terminate()
{
	m_shouldRun = false;
	m_cond.notify_one();
}