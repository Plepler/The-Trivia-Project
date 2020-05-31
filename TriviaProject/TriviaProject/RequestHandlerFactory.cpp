#include "RequestHandlerFactory.h"

//C'Tor, doesnt create database, passes it forward instead
RequestHandlerFactory::RequestHandlerFactory(IDataBase * db) :  m_loginManager(new LoginManager(db)), m_database(db)
{

}

//D'Tor
RequestHandlerFactory::~RequestHandlerFactory()
{

}



/*
Create a new login handler
*/
LoginRequestHandler RequestHandlerFactory::createLoginHandler()
{
	return LoginRequestHandler(m_database);
}



//Getter
LoginManager& RequestHandlerFactory::getLoginManager()
{
	return *m_loginManager;
}