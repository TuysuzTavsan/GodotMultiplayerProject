#pragma once

#include <client.h>
#include <handlerID.h>



struct ClientInfo
{
	ClientID m_clientID;
	HandlerID m_handlerID;

	ClientInfo()
		:
		m_clientID{0},
		m_handlerID{HandlerID::unspecified}
	{
				
	}

	ClientInfo(ClientID id)
		:
		m_clientID(id),
		m_handlerID(HandlerID::unspecified)
	{

	}

	~ClientInfo() = default;

	//Copy constructor is now prohibited.
	//ClientInfo(const ClientInfo& other) = delete;
	ClientInfo(const ClientInfo& other)
		:
		m_clientID{other.m_clientID},
		m_handlerID{other.m_handlerID}
	{

	}

	//Copy assignment operator is prohibited.
	//ClientInfo& operator=(const ClientInfo& other) = delete;
	ClientInfo& operator=(const ClientInfo& other)
	{
		m_clientID = other.m_clientID;
		m_handlerID = other.m_handlerID;

		return *this;
	}

	//Move constructor
	ClientInfo(ClientInfo&& other) noexcept
		:
		m_clientID{std::move(other.m_clientID)},
		m_handlerID{std::move(other.m_handlerID)}
	{
		
	}

	//Comparison operator
	friend bool operator<(const ClientInfo& left, const ClientInfo& right)
	{
		return left.m_clientID < right.m_clientID;
	}

	//Move assignment operator
	ClientInfo& operator=(ClientInfo&& other) noexcept
	{
		m_clientID = std::move(other.m_clientID);
		m_handlerID = std::move(other.m_handlerID);

		return *this;
	}

};