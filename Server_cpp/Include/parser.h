#pragma once

#include <client.h>

#include <iostream>

/*
Parser is the responsible class from parsing any type of incoming data from any peer.
Parser will also interact withh clientDistributor.
*/

class IParser
{
public:

	virtual ~IParser() {}
	virtual void Handle(ClientID peer, std::unique_ptr<char>&& data, size_t size) = 0;
};

class NULLParser : public IParser
{
public:

	void Handle(ClientID peer, std::unique_ptr<char>&& data, size_t size) override;
};


class Parser : public IParser
{
public:

	Parser();
	~Parser();

	void Handle(ClientID peer, std::unique_ptr<char>&& data, size_t size) override;

	//Forward
	//Unhandled datas
	//Process
	//Event according to incoming data.



private:

};