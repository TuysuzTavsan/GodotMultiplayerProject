#include <packet.h>
#include <stdexcept>

PacketOut::PacketOut()
	:
	m_to{nullptr},
	m_packet{nullptr},
	m_channel{0}
{

}

PacketOut::PacketOut(ENetPeer* to_peer, const void* data, const size_t& length,
	const std::uint32_t& flags, const std::uint8_t& channel)
	:
	m_to{to_peer},
	m_packet{enet_packet_create(data, length, flags)},
	m_channel{channel}
{
	if (!m_packet) //ENet Couldnt create packet.
	{
		throw std::exception("[EXCEPTION] ENet Couldnt create packet.");
	}
}

PacketOut::~PacketOut()
{
	//Leave deallocation to ENet.
}

PacketOut::PacketOut(PacketOut&& other) noexcept
	:
	m_to{ std::move(other.m_to) },
	m_packet{ std::move(other.m_packet) },
	m_channel{ std::move(other.m_channel) }
{

}

PacketOut& PacketOut::operator=(PacketOut&& other) noexcept
{
	if (m_packet)
	{
		enet_packet_destroy(m_packet);
	}

	m_to = std::move(other.m_to);
	m_packet = std::move(other.m_packet);
	m_channel = std::move(other.m_channel);

	return *this;
}

int PacketOut::Send()
{
	return enet_peer_send(m_to, m_channel, m_packet);
}











PacketIn::PacketIn()
	:
	m_owner{nullptr},
	m_id{0},
	m_prot{},
	m_data{},
	m_channel{0}
{

}

PacketIn::PacketIn(ENetPeer* owner, const ClientID& id, void* data, const size_t& size,
	const std::uint8_t& channel)
	:
	m_owner{owner},
	m_id{id},
	m_prot{},
	m_data{reinterpret_cast<char*>(data)},
	m_channel{channel}
{
	m_prot.Set(m_data);
}

PacketIn::~PacketIn()
{

}

PacketIn::PacketIn(PacketIn&& other) noexcept
	:
	m_owner{std::move(other.m_owner)},
	m_id{std::move(other.m_id)},
	m_prot{std::move(other.m_prot)},
	m_data{std::move(other.m_data)},
	m_channel{std::move(other.m_channel)}
{

}

PacketIn& PacketIn::operator=(PacketIn&& other) noexcept
{
	m_owner = std::move(other.m_owner);
	m_id = std::move(other.m_id);
	m_prot = std::move(other.m_prot);
	m_data = std::move(other.m_data);
	m_channel = std::move(other.m_channel);


	return *this;
}