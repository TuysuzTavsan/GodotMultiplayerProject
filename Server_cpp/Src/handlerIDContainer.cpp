//#include <handlerIDContainer.h>
//#include <stdexcept>
//#include <algorithm>
//
//HandlerIDContainer::HandlerIDContainer()
//	:
//	m_id{ HandlerID::unspecified },
//	m_handlers{}
//{
//
//}
//
//HandlerIDContainer::HandlerIDContainer(const HandlerID& id)
//	:
//	m_id{ id },
//	m_handlers{}
//{
//
//}
//
//HandlerID HandlerIDContainer::GetHandlerID()
//{
//	return m_id;
//}
//
//void HandlerIDContainer::SetHandlerID(const HandlerID& id)
//{
//	m_id = id;
//}
//
//void HandlerIDContainer::AddHandler(const IHandler& handler)
//{
//	//Check if already exist
//	auto it = std::find_if(m_handlers.begin(), m_handlers.end(),
//		[&handler](std::reference_wrapper<IHandler> item) { return &item.get() == &handler; }
//	);
//
//
//	//throw if exist
//	if (it != m_handlers.end())
//	{
//		throw std::exception("[EXCEPTION] IHandler already exist in the HandlerIDContainer.");
//	}
//
//	//if not push back
//	m_handlers.emplace_back(std::ref(handler));
//
//}
//
//
//void HandlerIDContainer::EraseHandler(IHandler& handler)
//{
//	auto it = std::erase_if(m_handlers,
//		[&handler](std::reference_wrapper<IHandler> item) {return &item.get() == &handler; }
//	);
//
//	if (it != 1)
//	{
//		if (it == 0)
//			throw std::exception("[EXCEPTION] Trying to erase non existing IHandler from HandlerIDContainer.");
//		else
//			throw std::exception("[EXCEPTION] Erased multiple IHandlers from HandlerIDContainer.");
//	}
//}