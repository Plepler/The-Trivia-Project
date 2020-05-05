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
#define MIN_LENGTH 5
#define BYTE2 1
#define BYTE3 2
#define BYTE4 3
#define BYTE5 4


class Communicator
{
public:
	void bindAndListen();
	void startHandleRequests();

private:
	void handleNewClient(SOCKET clientSocket);
	void clearBuffer(char * buffer);

	SOCKET _serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;


};