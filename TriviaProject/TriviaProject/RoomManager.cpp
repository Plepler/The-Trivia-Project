#include "RoomManager.h"

//C'Tor, pass pointer to Database, don't create new one.
RoomManager::RoomManager(IDataBase* db)
{
	m_database = db;
}



/*
This function creates a new room and adds it to the m_room map.
In: all the neccessery parameters for creating a room:

		name		  - the name of the room.
		maxUsers	  - maximum amount of users the room can have at the same time.
		questionCount - amount of question in the trivia.
		answerTimeout - number of second to answer each question.
*/
void RoomManager::createRoom(std::string roomName, unsigned int maxUsers, unsigned int questionCount, unsigned int answerTimeout)
{
	Room newRoom = Room(counter, roomName, maxUsers, questionCount, answerTimeout);
	m_rooms.insert(std::pair<unsigned int, Room*>(counter, &newRoom));
	counter++;
}



//This function removes a room from the map of rooms by its key (id)
void RoomManager::deleteRoom(int ID)
{
	m_rooms.erase(ID);
}



//Returns the state (IsActive) of the room from the m_rooms member.
unsigned int RoomManager::getRoomState(unsigned int ID)
{
	if (m_rooms.find(ID) == m_rooms.end()) 
	{
		// not found
		throw std::exception("Room doesn't exist");
	}

	return ((*m_rooms[ID]).getRoomData().isActive);
}



//Returns the vector RoomData from all rooms in m_rooms.
std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> roomsData;

	for (auto mapIter : m_rooms)
	{
		roomsData.push_back((*mapIter.second).getRoomData());
	}
	return roomsData;
}



//Returns a value (Room) of a key (ID) from m_rooms.
Room& RoomManager::getRoom(int id)
{
	for (auto i = m_rooms.begin(); i != m_rooms.end(); i++)
	{
		if ((*i).first == id)
		{
			return *(*i).second;
		}
	}
	throw std::exception("Room doesn't exist");
}
