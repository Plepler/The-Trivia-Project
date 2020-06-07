#include "RoomManager.h"


RoomManager::RoomManager(IDataBase* db)
{
	m_database = db;
}



void RoomManager::createRoom(std::string roomName, unsigned int maxUsers, unsigned int questionCount, unsigned int answerTimeout)
{
	int id = (*(--m_rooms.end())).first + 1;
	m_rooms.insert(std::pair<int, Room>(id, Room(id, roomName, maxUsers, questionCount, answerTimeout)));
}



void RoomManager::deleteRoom(int ID)
{

}

unsigned int RoomManager::getRoomState(int ID)
{
	return 0;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> roomsData;

	for (auto mapIter : m_rooms)
	{
		roomsData.push_back(mapIter.second.getRoomData());
	}
	return roomsData;
}

Room& RoomManager::getRoom(int id)
{
	for (auto i = m_rooms.begin(); i != m_rooms.end(); i++)
	{
		if ((*i).first == id)
		{
			return (*i).second;
		}
	}
	throw std::exception("Room doesn't exist");
}
