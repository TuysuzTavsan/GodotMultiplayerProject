#pragma once

#include <client.h>


/*
Parser is the responsible class from parsing any type of incoming data from any peer.
Parser will also interact withh clientDistributor.
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