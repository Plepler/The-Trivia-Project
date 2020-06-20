#pragma once
#include "SqliteDataBase.h"


class StatisticsManager
{
public:
	StatisticsManager(IDataBase* dataBase);
	~StatisticsManager();
	std::vector<std::string> getStatistics(std::string username);

private:
	IDataBase* m_database;
};

