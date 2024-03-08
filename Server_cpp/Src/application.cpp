#include <application.h>

#include <libHandler.h>
#include <locator.h>
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

	/* Provide ServiceLocator objects. */
	
	Locator::Init();

	Locator::ProvideParser(&m_parser);
	Locator::ProvideLobbyHandler(&m_lobbyHandler);

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

//TODO Make this thread awake at consistent intervals. SEARCH!
void Application::controlApp(bool& flag)
{
control:
	char input = 0;
	std::cin >> input;

	if (input == 'q')
	{
		flag = false;
	}
	else
	{
		goto control;
	}
}