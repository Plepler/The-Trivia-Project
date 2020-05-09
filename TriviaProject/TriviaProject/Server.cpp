#define _CRT_SECURE_NO_WARNINGS

#include "Server.h"


Server::Server() : m_database(new SqliteDataBase()), m_communicator(new Communicator(m_database, m_handlerFactory)), m_handlerFactory(new RequestHandlerFactory(m_database))
{
	m_database->open();
}

Server::~Server()
{
	m_database->close();
	delete m_database;
}


void Server::run()
{
	
	// the function that handle the conversation with the client
	thread t_connector(&Communicator::startHandleRequests, Communicator(m_database, m_handlerFactory));
	t_connector.detach();


	string input;
	cout << "Input 'EXIT' To exit: ";
	cin >> input;
	if (!cin)
		cin.clear();

	while (input != "EXIT")
	{
		cout << "Please enter a valid side. Try again: ";
		cin >> input;
		if (!cin)
			cin.clear();
	}

}

