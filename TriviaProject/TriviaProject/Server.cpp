#define _CRT_SECURE_NO_WARNINGS

#include "Server.h"




void Server::run()
{
	// the function that handle the conversation with the client
	thread t_connector(&Communicator::startHandleRequests, Communicator());
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

