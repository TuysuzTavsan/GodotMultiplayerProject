#pragma once

#include <parser.h>
#include <lobbyHandler.h>
#include <packetDispatcher.h>

/*
Service locator implementation taken from https://gameprogrammingpatterns.com/service-locator.html
Goal: provide easy access to application core structures without coupling or passing objects to constructor.
*/

class Locator
{
public:

	

	static void Init();


	static IParser& GetParser();

	static void ProvideParser(IParser* parser);


private:

	Locator() = default;
	~Locator() = default;

	static NULLParser m_nullParser;
	static IParser* m_parser;
};