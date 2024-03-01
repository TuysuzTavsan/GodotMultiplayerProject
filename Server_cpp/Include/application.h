#pragma once

#include <host.h>
#include <thread>

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
	bool shouldRun;
	std::jthread controlThrd; //TODO: change this to input controller thread.
};