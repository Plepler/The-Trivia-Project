#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"

class LoginRequestHandler;



class RequestHandlerFactory
{

public:
	RequestHandlerFactory(IDataBase* db);
	~RequestHandlerFactory();

	LoginRequestHandler createLoginHandler();
	LoginManager& getLoginManager();


private:
	LoginManager* m_loginManager;
	IDataBase* m_database;

};