#pragma once


#include <thread>

#include <host.h>
#include <eventDistributor.h>
#include <clientDistributor.h>
#include <packetDispatcher.h>
#include <lobbyHandler.h>

/*
Main Application struct.
*/

class Application
{
public:
	
	Application();

	~Application();

	bool Init();

	void Run();

	void Terminate();

private:

	void controlApp(bool& flag);

	Host m_host;
	LobbyHandler m_lobbyHandler;
	ClientDistributor m_clientDistributor;
	EventDistributor m_eventDistributor;
	PacketDispatcher m_packetDispatcher;
	bool shouldRun;
	std::jthread controlThrd; //TODO: change this to input controller thread.
	std::jthread dispatcherThrd;
};