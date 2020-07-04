#pragma once
#include "LoginManager.h"
#include "RoomManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
class LoginRequestHandler;
class MenuRequestHandler;



class RequestHandlerFactory
{

public:
	RequestHandlerFactory(IDataBase* db);
	~RequestHandlerFactory();

	LoginRequestHandler createLoginHandler();
	LoginManager& getLoginManager();

	MenuRequestHandler* createMenuRequestHandler(LoggedUser usr);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();


private:
	LoginManager* m_loginManager;
	IDataBase* m_database;
	RoomManager* m_roomManager;
	StatisticsManager * m_StatisticsManager; 



};