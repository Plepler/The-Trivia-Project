#include "LoginManager.h"

//C'Tor
LoginManager::LoginManager(IDataBase * db)
{
	m_database = db;
}

//D'Tor
LoginManager::~LoginManager()
{

}


/*FOR ALL FUNCTION BELOW

The function contant the database to insert / get information.
In case of failure or incorrect parametes, exceptions will be thrown

In: parameters neccessery for query.
*/



void LoginManager::signup(std::string username, std::string password, std::string email)
{
	if (email.find('@') == std::string::npos || email[0] == '@' || email[email.size() - 1] == '@')
	{
		throw std::exception("Invalid Email");
	}

	if (m_database->doseUserExist(username))
	{
		throw std::exception("User already exist");
	}

	m_database->addNewUser(username, password, email);
}



void LoginManager::login(std::string username, std::string password)
{
	
	if (!m_database->doseUserExist(username))
	{
		throw std::exception("Username doesn't exists");
	}

	if (!m_database->doesPasswordMatch(username, password))
	{
		throw std::exception("Incorrect password or username");
	}


	m_loggedUsers.push_back(LoggedUser(username));
}



void LoginManager::logout(std::string username)
{
	if (!m_database->doseUserExist(username))
	{
		throw std::exception("Username doesn't exists");
	}

	//Find user in vector and delete him.
	for (std::vector<LoggedUser>::iterator vIter = m_loggedUsers.begin(); vIter != m_loggedUsers.end(); vIter)
	{
		if (vIter->getUsername() == username)
		{
			m_loggedUsers.erase(vIter);
			return;
		}
	}

	throw std::exception("User isn't logged");
	
}