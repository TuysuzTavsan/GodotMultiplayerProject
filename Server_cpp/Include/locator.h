#pragma once

#include <eventDistributor.h>
#include <lobbyHandler.h>
#include <packetDispatcher.h>
#include <clientDistributor.h>

/*
Service locator implementation taken from https://gameprogrammingpatterns.com/service-locator.html
Goal: provide easy access to application core structures without coupling or passing objects to constructor.
*/

class Locator
{
public:

	static void Init();
	
	static void ProvideEventDistributor(IEventDistributor* eventDistributor);
	static IEventDistributor& GetEventDistributor();

	static void ProvideLobbyHandler(ILobbyHandler* lobbyHandler);
	static ILobbyHandler& GetLobbyHandler();

	static void ProvideClientDistributor(IClientDistributor* clientDistributor);
	static IClientDistributor& GetClientDistributor();

private:

	Locator() = default;
	~Locator() = default;

	static NULLEventDistributor m_nullEventDistributor;
	static IEventDistributor* m_eventDistributor;
	
	static NULLLobbyHandler m_nullLobbyHandler;
	static ILobbyHandler* m_lobbyHandler;

	static NULLClientDistributor m_nullClientDistributor;
	static IClientDistributor* m_clientDistributor;
};