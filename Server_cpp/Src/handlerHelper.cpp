#include <handlerHelper.h>
#include <stdexcept>



void HandlerHelper::Subscribe(IHandler& handler)
{

	auto temp = m_handlers.find(handler.GetID());

	if (temp != m_handlers.end())
	{
		//Already subscribed.
		throw std::exception("[EXCEPTION] IHandler already subscribed");
	}

	m_handlers.emplace(handler.GetID(), std::ref(handler));
	
}

void HandlerHelper::Unsubscribe(IHandler& handler)
{
	auto temp = m_handlers.find(handler.GetID());

	if (temp == m_handlers.end())
	{
		throw std::exception("[EXCEPTION] Trying to remove unexisting IHandler.");
	}

	m_handlers.erase(temp);
}

std::reference_wrapper<IHandler> HandlerHelper::GetSubscriber(const HandlerID& id)
{
	auto temp = m_handlers.find(id);

	if (temp == m_handlers.end())
	{
		throw std::exception("[EXCEPTION] Trying to get unsubscribed IHandler.");
	}

	return std::ref(temp->second);
}

std::reference_wrapper<IHandler> HandlerHelper::GetSubscriber(const HandlerID&& id)
{
	auto temp = m_handlers.find(id);

	if (temp == m_handlers.end())
	{
		throw std::exception("[EXCEPTION] Trying to get unsubscribed IHandler.");
	}

	return std::ref(temp->second);
}


std::map<HandlerID, std::reference_wrapper<IHandler>> HandlerHelper::m_handlers;