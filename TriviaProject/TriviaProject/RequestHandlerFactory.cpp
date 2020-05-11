#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDataBase * db) :  m_loginManager(new LoginManager(db)), m_database(db)
{

}

RequestHandlerFactory::~RequestHandlerFactory()
{

}


LoginRequestHandler RequestHandlerFactory::createLoginHandler()
{
	return LoginRequestHandler(m_database);
}


LoginManager& RequestHandlerFactory::getLoginManager()
{
	
	return *m_loginManager;
}