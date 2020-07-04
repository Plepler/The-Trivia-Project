#pragma once
#include "Room.h"
#include "LoggedUser.h"
#include "SqliteDataBase.h"
#include <vector>
#include <map>


class RoomManager
{
public:
	RoomManager(IDataBase * db);
	void createRoom(std::string roomName, unsigned int maxUsers, unsigned int questionCount, unsigned int answerTimeout);
	void deleteRoom(int ID);
	unsigned int getRoomState(unsigned int ID);
	std::vector<RoomData> getRooms();
	Room& getRoom(int id);

private:
	unsigned int counter = 0;
	std::map<unsigned int, Room*> m_rooms;
	IDataBase* m_database;
};