#include "RoomManager.h"

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> roomsData;

	for (auto mapIter : m_rooms)
	{
		roomsData.push_back(mapIter.second.getRoomData());
	}
	return roomsData;
}
