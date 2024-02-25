#include <libHandler.h>
#include <host.h>
#include <thread>
#include <iostream>

void controlApp(bool& flag)
{
	char input = 0;
	std::cin >> input;

	if (input == 'q')
	{
		flag = false;
	}
}

int main()
{
	if (!LibHandler::Init())
	{
		return -1;
	}

	Host mhost;
	
	bool run = true;

	std::thread controlthrdd(controlApp, std::ref(run));

	while (run)
	{
		mhost.PollEvents();
	}


	LibHandler::DeInit();
	controlthrdd.join();

	return 0;
}