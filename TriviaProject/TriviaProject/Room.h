#pragma once

struct RoomData
{
	unsigned intid;
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
	void getAllUsers();


private:

	RoomData m_metadata;
	std::vector<LoggedUser> m_users;

};

