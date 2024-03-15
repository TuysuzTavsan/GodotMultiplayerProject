#include <application.h>

int main()
{

	Application app;

	if (!app.Init())
	{
		return -1;
	}

	app.Run();

	app.Terminate();


	_CrtDumpMemoryLeaks();

	return 0;
}