#include <libHandler.h>
#include <host.h>

int main()
{
	if (!LibHandler::Init())
	{
		return -1;
	}

		Host mhost;
	

	LibHandler::DeInit();


	return 0;
}