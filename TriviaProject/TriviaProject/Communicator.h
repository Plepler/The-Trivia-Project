#pragma once

#include "RequestHandlerFactory.h"
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
#include <mutex>

#define PORT 42069
#define MAX_SIZE 100
#define MIN_LENGTH 5
#define GREETING "hello"


class Communicator
{

public:
	Communicator(IDataBase* db, RequestHandlerFactory* handlerFactory);
	void bindAndListen();
	void startHandleRequests();

private:
	void handleNewClient(SOCKET clientSocket);

	//Helper functions
	void sendData(SOCKET clientSocket, std::vector<unsigned char>& data);
	void recieveData(SOCKET clientSocket, std::vector<unsigned char>& data, unsigned int size);


	SOCKET _serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory* m_handlerFactory;
	IDataBase* _db;

};