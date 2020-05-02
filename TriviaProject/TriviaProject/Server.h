#pragma once

#include "Communicator.h"


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

