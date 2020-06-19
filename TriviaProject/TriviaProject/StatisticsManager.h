#pragma once
#include "SqliteDataBase.h"

class StatisticsManager
{
public:
	StatisticsManager(IDataBase* dataBase);
	~StatisticsManager();
	void getStatistics();
private:
	IDataBase* m_database;
};