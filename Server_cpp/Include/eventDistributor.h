#pragma once

#include <client.h>


/*
EventDistributor is the responsible class from parsing TopProtocol of incoming packets from any peer.
It will forward packets depending on TopProtocol.
This class is not thread safe.
*/

class IEventDistributor
{
public:

	virtual ~IEventDistributor() {}
	virtual void Handle(const ENetEvent& event) = 0;
};

class NULLEventDistributor : public IEventDistributor
{
public:

	void Handle(const ENetEvent& event) override;
};


class EventDistributor : public IEventDistributor
{
public:

	EventDistributor();
	~EventDistributor();

	void Handle(const ENetEvent& event) override;

	//Forward
	//Unhandled datas
	//Process
	//Event according to incoming data.



private:

};