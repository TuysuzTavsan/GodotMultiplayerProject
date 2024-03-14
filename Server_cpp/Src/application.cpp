#include <application.h>

#include <libHandler.h>
#include <locator.h>
#include <iostream>


Application::Application()
	:
	m_host{},
	shouldRun{true},
	controlThrd{&Application::controlApp, &*this, std::ref(this->shouldRun)},
	dispatcherThrd{&PacketDispatcher::Dispatch, std::ref(m_packetDispatcher)}
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

	Locator::ProvidePacketDispatcher(&m_packetDispatcher);
	Locator::ProvideEventDistributor(&m_eventDistributor);
	Locator::ProvideLobbyHandler(&m_lobbyHandler);
	Locator::ProvideClientDistributor(&m_clientDistributor);

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
	m_packetDispatcher.Terminate();
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