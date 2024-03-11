#pragma once

#include <host.h>
#include <thread>
#include <eventDistributor.h>
#include <lobbyHandler.h>
#include <clientDistributor.h>

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
	bool shouldRun;
	std::jthread controlThrd; //TODO: change this to input controller thread.
};