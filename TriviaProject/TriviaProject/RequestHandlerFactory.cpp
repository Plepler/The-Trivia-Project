#include "RequestHandlerFactory.h"

//C'Tor, doesnt create database, passes it forward instead
RequestHandlerFactory::RequestHandlerFactory(IDataBase * db) :  m_loginManager(new LoginManager(db)), m_database(db), m_roomManager(new RoomManager(m_database)), m_StatisticsManager(nullptr)
{

}



//D'Tor
RequestHandlerFactory::~RequestHandlerFactory()
{
	//clear memory of all allocated managers
	if (m_StatisticsManager != nullptr)
	{
		delete m_StatisticsManager;
		m_StatisticsManager = nullptr;
	}
	if (m_loginManager != nullptr)
	{
		delete m_loginManager;
		m_loginManager = nullptr;
	}
	if (m_roomManager != nullptr)
	{
		delete m_roomManager;
		m_roomManager = nullptr;
	}
}



/*
Create a new login handler
*/
LoginRequestHandler* RequestHandlerFactory::createLoginHandler()
{
	return new LoginRequestHandler(m_database);
}



//Getter
LoginManager& RequestHandlerFactory::getLoginManager()
{
	return *m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser usr)
{
	m_StatisticsManager = new StatisticsManager(m_database);
	return new MenuRequestHandler(usr, this);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return *m_StatisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return *m_roomManager;
}
