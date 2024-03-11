#pragma once

#include <enet/enet.h>

/*
Host is responsible from constantly polling and distributing server events such as:
Peer connected, peer disconnected, data received.
*/
class Host {
public:

	//Creates host connection with the information in ServerInfo namespace. see namespace ServerInfo. Will throw if error occures while creating Host.
	Host();
	~Host();

	//copy constructor is forbidden.
	Host(const Host&) = delete;
	//copy assignment is deleted
	Host& operator=(const Host&) = delete;

	void CreateServer();

	//Poll and manage events.
	void PollEvents();


private:

	ENetAddress m_address;
	ENetHost* m_server;
};