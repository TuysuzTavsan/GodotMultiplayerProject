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

void IHandler::AddClient(std::reference_wrapper<Client>&& client)
{
	//Check if already there.
	auto it = std::find_if(m_clients.begin(), m_clients.end(), 
		[&client](std::reference_wrapper<Client>& element) {return client.get() == element.get(); }
	);

	if (it != m_clients.end())
	{
		//Already exists.
		throw std::exception("[EXCEPTION] Trying to add already existing client.");
	}

	m_clients.push_back(std::move(client));
}

void IHandler::EraseClient(std::reference_wrapper<Client>& client)
{
	//Check if exists.
	auto it = std::find_if(m_clients.begin(), m_clients.end(),
		[&client](std::reference_wrapper<Client>& element) {return client.get() == element.get(); }
	);

	if (it == m_clients.end())
	{
		//Cant find
		throw std::exception("[EXCEPTION] Trying to erase nonexisting client.");
	}

	m_clients.erase(it);
}