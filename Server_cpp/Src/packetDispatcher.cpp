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
		m_cond.wait(lck,
			[this](){
				if (m_packetIn.size() || !m_shouldRun)
				{
					return true;
				}
				return false;
			});

		//TODO check the swap
		m_packetIn.swap(m_packetOut);

		lck.unlock();

		for (auto it = m_packetOut.begin(); it != m_packetOut.end();)
		{
			if (it->Send() == 0)
			{
				std::cout << "Successfully sended packet.\n";
			}
			else
			{
				std::cout << "[ERROR] PacketDispatcher failed to send out packet.\n";
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
	std::scoped_lock lck(m_mut);

	m_shouldRun = false;
	m_cond.notify_one();
}