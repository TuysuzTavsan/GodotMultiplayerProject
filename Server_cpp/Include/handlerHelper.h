#pragma once

#include <map>
#include <vector>

#include <ihandler.h>

/*
Static helper class to work with IHandler interface.
IHandlers can subscribe to a handlerID enum with Subscribe, and can also unsubscribe.
ClientDistributor will distribute peers with the help of this interface.

Note: This implementation forces every IHandler to have only one HandlerID.
This class is not thread safe.
*/

class HandlerHelper
{
public:

	//Subscribe to a handlerID
	static void Subscribe(IHandler& handler);

	//Unsubscribe to a handlerID
	static void Unsubscribe(IHandler& handler);

	//Return the IHandlers that subscribed to specified ID
	static std::reference_wrapper<IHandler> GetSubscriber(const HandlerID& id);

	//Return the IHandlers that subscribed to specified ID
	static std::reference_wrapper<IHandler> GetSubscriber(const HandlerID&& id);

	static void Forward();


private:

	HandlerHelper() = default;
	~HandlerHelper() = default;

	static std::map<HandlerID, std::reference_wrapper<IHandler>> m_handlers;

};