#pragma once
#include "LoginManager.h"
#include "RoomManager.h"
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
	RoomManager m_roomManager;
	//StatisticsManager m_StatisticsManager; Doesnt exist for now



};