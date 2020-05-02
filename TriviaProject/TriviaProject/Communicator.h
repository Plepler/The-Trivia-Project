#pragma once

#include "LoginRequestHandler.h"
#include <WinSock2.h>
#include <Windows.h>
#include <set>
#include <string>
#include <exception>
#include <iostream>
#include <thread>
#include <Mutex>
#include <cmath>
#include <map>

#define PORT 42069
#define MAX_SIZE 100

class Communicator
{
public:
	void bindAndListen();
	void startHandleRequests();

private:
	void handleNewClient(SOCKET clientSocket);

	SOCKET _serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;


};