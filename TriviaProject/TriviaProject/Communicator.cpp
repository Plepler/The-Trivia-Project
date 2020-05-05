#pragma comment(lib, "Ws2_32.lib")
#include "Communicator.h"





void Communicator::startHandleRequests()
{
	SOCKET client_socket = 0;
	_serverSocket = 0;

	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__ " - socket");


	this->bindAndListen();

	while (true)
	{
		std::cout << "Waiting for client connection request" << std::endl;


		// this accepts the client and create a specific socket from server to this client
		client_socket = ::accept(_serverSocket, NULL, NULL);

		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		std::cout << "Client accepted. Server and client can speak" << std::endl;

		//Add socket to client map
		m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, nullptr));

		// the function that handle the conversation with the client
		std::thread t(&Communicator::handleNewClient, this, client_socket);
		t.detach();

		std::cout << std::endl;
	}

	//Close all sockets
	for (std::pair<SOCKET, IRequestHandler*> m_iter : m_clients)
	{
		try
		{
			closesocket(m_iter.first);
		}
		catch (...) {}
	}

	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}

}



void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*) & sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;
}



void Communicator::handleNewClient(SOCKET clientSocket)
{
	unsigned int length = 0;
	char buffer[MAX_SIZE] = { 0 };
	std::string message;
	RequestInfo newReq;
	RequestResult rr;

	//Send hello
	std::string data("Hello");
	if (send(clientSocket, data.c_str(), data.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}

	recv(clientSocket, buffer, MAX_SIZE - 1, 0);
	std::cout << std::string(buffer) << std::endl;

	while (true)
	{
		clearBuffer(buffer);
		recv(clientSocket, buffer, MIN_LENGTH, 0);
		time(&(newReq.recievelTime));
		newReq.id = int(buffer[0]);
		length = (int)(buffer[BYTE2] << 24 | buffer[BYTE3] << 16 | buffer[BYTE4] << 8 | buffer[BYTE5]);//Convert 4 Bytes to int
		clearBuffer(buffer);
		recv(clientSocket, (char*)&(newReq.buffer[0]), length, 0);
		rr = m_clients.at(clientSocket)->handleRequest(newReq);



		if (send(clientSocket, (char*)&rr.response, data.size(), 0) == INVALID_SOCKET)
		{
			throw std::exception("Error while sending message to client");
		}
	}

	
}



void Communicator::clearBuffer(char* buffer)
{
	for (size_t i = 0; i < MAX_SIZE; i++)
	{
		buffer[i] = 0;
	}
}