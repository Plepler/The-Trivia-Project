#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDataBase * db) :  m_loginManager(new LoginManager(db)), m_database(db)
{

}

RequestHandlerFactory::~RequestHandlerFactory()
{

}


LoginRequestHandler RequestHandlerFactory::createLoginHandler()
{
	return LoginRequestHandler(nullptr);
}


LoginManager& RequestHandlerFactory::getLoginManager()
{
	LoginManager temp(nullptr);
	return temp;
}