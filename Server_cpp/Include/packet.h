#pragma once

#include <enet/enet.h>
#include <client.h>
#include <protocol.h>
#include <string>
#include <cstdint>

struct PacketOut
{
	ENetPeer* m_to;
	ENetPacket* m_packet;
	std::uint8_t m_channel;

	PacketOut();
	PacketOut(ENetPeer* to_peer, const Protocol& prot, const std::string& data,
		const std::uint32_t& flags, const std::uint8_t& channel);

	PacketOut(ENetPeer* to_peer, const void* data, const size_t& length,
		const std::uint32_t& flags, const std::uint8_t& channel);
	~PacketOut();

	//copy constructor is prohibited.
	PacketOut(const PacketOut& other) = delete;

	//copy assignment operator is prohibited.
	PacketOut& operator=(const PacketOut& other) = delete;

	//Move constructor.
	PacketOut(PacketOut&& other) noexcept;

	//Move assignment operator.
	PacketOut& operator=(PacketOut&& other) noexcept;

	//Send packet. Returns 0 if succeeds otherwise <0.
	int Send();
};

struct PacketIn
{
	ENetPeer* m_owner;
	ClientID m_id;
	Protocol m_prot;
	std::string m_data;
	std::uint8_t m_channel;
	
	PacketIn();
	PacketIn(ENetPeer* owner, const ClientID& id, void* data, const size_t& size,
		const std::uint8_t& channel);
	~PacketIn();

	//copy constructor is prohibited.
	PacketIn(const PacketIn& other) = delete;

	//copy assignment operator is prohibited.
	PacketIn& operator=(const PacketIn& other) = delete;
	
	//Move constructor.
	PacketIn(PacketIn&& other) noexcept;

	//Move assignment operator.
	PacketIn& operator=(PacketIn&& other) noexcept;
};