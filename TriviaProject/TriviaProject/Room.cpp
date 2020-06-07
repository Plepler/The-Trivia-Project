#include "Room.h"

Room::Room(int id, std::string roomName, unsigned int maxUsers, unsigned int questionCount, unsigned int answerTimeout)
{
	m_metadata.id = id;
	m_metadata.isActive = true;
	m_metadata.maxPlayers = maxUsers;
	m_metadata.timePerQuestion = answerTimeout;
	m_metadata.name = roomName;
}

void Room::addUser(LoggedUser user)
{
	m_users.push_back(user);
}

/*
This function removes the user it gets as parameter
In: The user we want to remove
*/
void Room::removeUser(LoggedUser user)
{
	auto vectorIter = m_users.begin();
	while (vectorIter != m_users.end())
	{
		if ((*vectorIter).getUsername() == user.getUsername())
		{
			m_users.erase(vectorIter);
		}
		vectorIter++;
	}
	
}



/*
This function returns the vector of users
Out: the function memeber m_users which is all users in the room
*/
std::vector<LoggedUser> Room::getAllUsers()
{
	return m_users;
}



/*
This function returns the meta data about a room
Out: Meta data struct, info about the room:
		id				- The room's id (unique)
		name			- The room's name (unique?)
		maxPlayers		- Maximum capacity of players in the room
		timePerQuestion - Time to answer each question
		isActive		- Is room in active
*/
RoomData Room::getRoomData()
{
	return m_metadata;
}
