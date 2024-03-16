#pragma once

/*
Handles all 3rd party libraries.
If any initialization fails during LibHandler.Init() it will return false, otherwise true.
It will also deinitialize every 3rd party library when DeInitialize() called.
This class is not thread safe.
*/
class Librarian
{
public:

	//Initialize every 3rd party library. Returns false if fails, otherwise true. Must be called only once!
	static bool Init();

	//DeInitialize every 3rd party library. Must be called once at the end of the program.
	static void DeInit();

	/* Hide away constructor and destructor, No need for it. */
private:

	Librarian() = default;
	~Librarian() = default;

};