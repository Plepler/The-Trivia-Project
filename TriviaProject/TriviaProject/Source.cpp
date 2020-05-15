#include "Server.h"
#include "WSAInitializer.h"

//Temperary main
int main()
{
	WSAInitializer w;//Neccessery for socket - server connection
	Server s;
	s.run();

	return 0;
}