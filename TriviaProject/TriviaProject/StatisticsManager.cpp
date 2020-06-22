#include "StatisticsManager.h"


//C'Tor
StatisticsManager::StatisticsManager(IDataBase * dataBase)
{
	this->m_database = dataBase;
}
//D'Tor
StatisticsManager::~StatisticsManager()
{

}



/*
This function calls all the statistics function from the database and creates the stats struct
In: User
Out: stats struct of the player
*/
std::vector<std::string> StatisticsManager::getStatistics(std::string username)
{
	std::vector<std::string> stats;
	stats.push_back(std::to_string(m_database->getPlayerAvarageAnswerTime(username)));
	stats.push_back(std::to_string(m_database->getNumOfCorrectAnswers(username)));
	stats.push_back(std::to_string(m_database->getNumOfTotalAnswers(username)));
	stats.push_back(std::to_string(m_database->getNumOfPlayerGames(username)));

	return stats;
}