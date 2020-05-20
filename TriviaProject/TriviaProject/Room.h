#pragma once
#include "LoggedUser.h"


struct RoomData
{
	unsigned int id;
	std::string name;
	std::string maxPlayers;
	unsigned int timePerQuestion;
	unsigned int isActive;

}typedef RoomData;


class Room
{
public:
	void addUser();
	void removeUser();
	std::vector<LoggedUser> getAllUsers();
	RoomData getRoomData();


private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;

};

