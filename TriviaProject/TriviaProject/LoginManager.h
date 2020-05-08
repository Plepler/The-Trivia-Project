#pragma once
#include "SqliteDataBase.h"

class LoginManager
{

public:
	LoginManager();
	~LoginManager();
	void signup(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout(std::string username);



private:

	IDataBase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};