#include "LoggedUser.h"

//C'Tor
LoggedUser::LoggedUser(std::string username)
{
	this->m_username = username;
}

//Getter
std::string LoggedUser::getUsername()
{
	return m_username;
}
