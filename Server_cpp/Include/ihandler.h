#pragma once

#include <handlerID.h>
#include <clientInfo.h>
#include <client.h>
#include <map>
#include <memory>

/*
Interface that every handler class derives from except libHandler.
You can only set ID of this class once.
Trying to set ID for the second time will result in throw.

*/

class IHandler
{
public:

	IHandler();
	virtual ~IHandler() = default;

	//Copy constructor is prohibited.
	IHandler(const IHandler& other) = delete;

	//Copy assignment operator is prohibited.
	IHandler& operator=(const IHandler& other) = delete;

	//Get ID of the handler.
	HandlerID GetID();

	//Set ID of the Handler. 
	//This function will also call HandlerHelper::Subscribe and seal this class.
	//Calling this method for the second time will throw.
	void SetID(const HandlerID& id);

	//Add client to the Handlers pool by reference.
	void AddClient(const ClientInfo& info, std::reference_wrapper<Client> client);

	//Remove client from the Handlers pool.
	void EraseClient(const ClientInfo& info);

	//Input incoming msg from responsible client.
	void Input();	


private:

	bool m_sealed;  // flag to prevent from setting ID second time.
	HandlerID m_id; // ID of the Handler
	std::map<ClientInfo, std::reference_wrapper<Client>> m_clients;

};