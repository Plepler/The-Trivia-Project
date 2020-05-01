#pragma once
#include "LoginRequestHandler.h"
#include <WinSock2.h>
#include <Windows.h>
#include <map>


class Communicator
{
public:
	void bindAndListen();
	void startHandleRequests();

private:
	void handleNewClient();



	std::map<SOCKET, IRequestHandler*> m_clients;


};