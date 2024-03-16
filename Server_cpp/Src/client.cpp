#include <client.h>

#include <packetDispatcher.h>
#include <locator.h>

#include <utility>

Client::Client(ENetPeer* peer)
	:
	m_peer{ peer },
	m_userName{}
{

}

Client::Client(Client&& other) noexcept
	:
	m_peer{ std::move(other.m_peer) },
	m_userName{std::move(other.m_userName)}
{

}

Client::~Client()
{
	//ENet will handle peer
}

Client& Client::operator=(Client&& other) noexcept
{
	m_peer = std::move(other.m_peer);
	m_userName = std::move(other.m_userName);

	return *this;
}

bool Client::operator==(const Client& other) const
{
	return m_peer == other.m_peer;
}

void Client::Send(const std::string& msg, const std::uint8_t& channel, const ENetPacketFlag& flag)
{
	PacketOut myPacket(m_peer, msg.data(), msg.length(), flag, channel);
	Locator::GetPacketDispatcher().PutPacket(std::move(myPacket));
}

ENetPeer* Client::Get()
{
	return m_peer;
}

void Client::SetUserName(const std::string& name)
{
	m_userName = name;
}

std::string Client::GetName()
{
	return m_userName;
}