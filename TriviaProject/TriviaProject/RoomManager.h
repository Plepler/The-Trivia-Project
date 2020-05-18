#pragma once
#include "Room.h"
#include "LoggedUser.h"
#include <vector>
#include <map>


class RoomManager
{
public:
	void createRoom(LoggedUser);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();


private:
	std::map<int, Room> m_rooms;
};