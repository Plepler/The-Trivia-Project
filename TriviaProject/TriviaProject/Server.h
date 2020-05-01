#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include <exception>
#include <iostream>
#include <thread>
#include "Communicator.h"

#define PORT 42069


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::exception;
using std::thread;

class Server
{

public:
	void run();



private:
	Communicator m_communicator;

};

