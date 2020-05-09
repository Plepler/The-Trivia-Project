#pragma once

#include "Communicator.h"
#include "IDataBase.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::exception;
using std::thread;

class Server
{

public:
	Server();
	~Server();
	void run();



private:
	Communicator* m_communicator;
	IDataBase* m_database;
	RequestHandlerFactory* m_handlerFactory;
	

};

