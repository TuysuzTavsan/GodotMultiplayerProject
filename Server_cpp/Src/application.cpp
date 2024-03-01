#include <application.h>

#include <libHandler.h>
#include <iostream>

Application::Application()
	:
	m_host{},
	shouldRun{true},
	controlThrd{&Application::controlApp, &*this, std::ref(this->shouldRun)}
{

}

Application::~Application()
{
	
}

bool Application::Init()
{
	if (!LibHandler::Init())
	{
		return false;
	}

	m_host.CreateServer();

	return true;
}

void Application::Run()
{
	while (shouldRun)
	{
		m_host.PollEvents();
	}
}

void Application::Terminate()
{
	LibHandler::DeInit();
}

void Application::controlApp(bool& flag)
{
	char input = 0;
	std::cin >> input;

	if (input == 'q')
	{
		flag = false;
	}
}