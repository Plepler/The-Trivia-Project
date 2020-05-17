#define _CRT_SECURE_NO_WARNINGS

#include "Server.h"


//C'Tor, Only here will the database will be created / opened
Server::Server() : m_database(new SqliteDataBase()), m_communicator(new Communicator(m_database, m_handlerFactory)), m_handlerFactory(new RequestHandlerFactory(m_database))
{
	m_database->open();
}


//D'Tor
Server::~Server()
{
	m_database->close();
	delete m_database;
}



/*
This function will create the communicator thread
It will wait for 'EXIT' input and will close the server then.
*/
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

