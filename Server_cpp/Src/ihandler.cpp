#include <ihandler.h>
#include <algorithm>
#include <stdexcept>
#include <handlerHelper.h>

IHandler::IHandler()
	:
	m_sealed{false},
	m_id{HandlerID::unspecified}
{

}

HandlerID IHandler::GetID()
{
	return m_id;
}

void IHandler::SetID(const HandlerID& id)
{
	if (!m_sealed)
	{
		m_id = id;
		m_sealed = true;
		HandlerHelper::Subscribe(*this);
	}
	else
	{
		throw std::exception("[EXCEPTION] Trying to setID of the IHandler for second time.");
	}
		
}

void IHandler::AddClient(const ClientInfo& info, std::reference_wrapper<Client> client)
{
	//Check if already there.
	auto it = m_clients.find(info);

	if (it != m_clients.end())
	{
		//Already exists.
		throw std::exception("[EXCEPTION] Trying to add already existing client.");
	}

	m_clients.emplace(info, client);
}

void IHandler::EraseClient(const ClientInfo& info)
{
	//Check if exists.
	auto it = m_clients.find(info);

	if (it == m_clients.end())
	{
		//Cant find
		throw std::exception("[EXCEPTION] Trying to erase nonexisting client.");
	}

	m_clients.erase(it);
}