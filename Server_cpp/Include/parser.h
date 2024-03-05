#pragma once

#include <enet/enet.h>

#include <iostream>

/*
Parser is the responsible class from parsing any type of incoming data from any peer.
Parser will also interact withh clientDistributor.
*/

class IParser
{
public:

	virtual ~IParser() {}
	virtual void Handle(ENetPeer* peer, std::unique_ptr<char>&& data, size_t size) = 0;
};

class NULLParser : public IParser
{
public:

	void Handle(ENetPeer* peer, std::unique_ptr<char>&& data, size_t size) override
	{
		/*Do nothing*/
		std::cout << "[NULLParser is Provided]\n";
	}
};


class Parser : public IParser
{
public:

	Parser() {}
	~Parser() {}

	void Handle(ENetPeer* peer, std::unique_ptr<char>&& data, size_t size) override
	{
		std::cout << "Message says:\n\t";

		for (int i = 0; i < size; i++)
		{
			std::cout << data.get()[i];
		}

		std::cout << "\n";
	}

	//Forward
	//Unhandled datas
	//Process
	//Event according to incoming data.



private:

};