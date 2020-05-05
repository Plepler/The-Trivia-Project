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
	std::vector<unsigned char> buffer;
	std::string message;
	RequestInfo newReq;
	RequestResult request_result;
	message = GREETING;


	try
	{
		buffer.insert(buffer.begin(), message.begin(), message.end());

		sendData(clientSocket, buffer);

		recieveData(clientSocket, buffer, MIN_LENGTH);

		if (buffer[0] == GREETING[0] && buffer[1] == GREETING[1] && buffer[2] == GREETING[2] && buffer[3] == GREETING[3] && buffer[4] == GREETING[4])
		{
			std::cout << buffer[0] << buffer[1] << buffer[2] << buffer[3] << buffer[4] << std::endl;
		}
		else
		{
			throw std::exception("We begin with 'hello'");
		}
		
	
	
		while (true)
		{
			recieveData(clientSocket, buffer, MIN_LENGTH);
			time(&(newReq.recievelTime));
			newReq.id = int(buffer[0]);//First byte is request id
			length = int((unsigned char)(buffer[BYTE2]) << LSH24 |
						 (unsigned char)(buffer[BYTE3]) << LSH16 |
						 (unsigned char)(buffer[BYTE4]) << LSH8 |
						 (unsigned char)(buffer[BYTE5]));

			recieveData(clientSocket, buffer, length);

			request_result = m_clients.at(clientSocket)->handleRequest(newReq);//Handle request and get appropiate response

			sendData(clientSocket, buffer);
		}
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
}



void Communicator::clearBuffer(char* buffer)
{
	for (size_t i = 0; i < MAX_SIZE; i++)
	{
		buffer[i] = 0;
	}
}

void Communicator::sendData(SOCKET clientSocket, std::vector<unsigned char>& data)
{
	if (send(clientSocket, (char*)&data, data.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

void Communicator::recieveData(SOCKET clientSocket, std::vector<unsigned char>& data, unsigned int size)
{
	data.clear();
	if (recv(clientSocket, (char*)&data, size, 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while recieving data");
	}
}