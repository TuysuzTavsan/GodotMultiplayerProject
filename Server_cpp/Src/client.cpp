#include <client.h>

#include <utility>

Client::Client(ENetPeer* peer)
	:
	m_peer{ peer }
{

}

Client::Client(Client&& other) noexcept
	:
	m_peer{ std::move(other.m_peer) }
{

}

Client::~Client()
{
	//ENet will handle peer
}

Client& Client::operator=(Client&& other) noexcept
{
	m_peer = std::move(other.m_peer);

	return *this;
}

bool Client::operator==(const Client& other) const
{
	return m_peer == other.m_peer;
}

void Client::Send(const std::string& msg, std::uint8_t channel, const ENetPacketFlag& flag)
{
	/* Create a reliable packet of size 7 containing "packet\0" */
	const void* data = static_cast<const void*>(msg.data()); //already null terminated in c++11
	size_t size = msg.size();



	ENetPacket* packet = enet_packet_create(data, size, flag); // void* data, size, flag

	//TODO
	//MSGSENDER::ADDPACKET(m_peer, channel, packet);
}

ENetPeer* Client::Get()
{
	return m_peer;
}
