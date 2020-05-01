#include "Server.h"
#include "WSAInitializer.h"

int main()
{
	WSAInitializer w;
	Server s;
	s.run();
	return 0;
}