#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room* room, LoggedUser* loggedUser, RequestHandlerFactory* hanlderFactory)
{
	m_room = room;
	m_user = loggedUser;
	m_handlerFactory = hanlderFactory;
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo request)
{
    bool flag = false;
    if (request.id == LEAVE || request.id == STATE)
    {
        flag = true;
    }
    return flag;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo request)
{
	RequestResult requestRes{ std::vector<unsigned char>(), nullptr };

	if (isRequestRelevant(request))
	{
		switch (request.id)
		{
		case LEAVE:
			requestRes = leaveRoom(request);
			break;

		case STATE:
			requestRes = getRoomState(request);
			break;

		default:
			requestRes.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ "Error with request id" });
			break;
		}
	}
	else
	{
		//If excpetions are thrown about the request type they will be caught here
		requestRes.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ "Request doesnt Exist" });
	}

	return requestRes;
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo request)
{
	RequestResult result;
	LeaveRoomResponse leaveRes{ 1 };
	try
	{
		result.response = JsonResponsePacketSerializer::serializeResponse(leaveRes);
		result.newHandler = m_handlerFactory->createMenuRequestHandler(*m_user);
	}
	catch (std::exception e)//If serialization failed the error will be serialized instead
	{
		result.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo request)
{
	RequestResult result;
	
	std::vector<std::string> players;

	//Create vector of usernames
	for (LoggedUser user : m_room->getAllUsers())
	{
		players.push_back(user.getUsername());
	}

	try
	{
		//build response
		GetRoomStateResponse stateRes{ 1, m_room->getRoomData().isActive, players , m_room->getRoomData().numOfQuestions, m_room->getRoomData().timePerQuestion};
		result.response = JsonResponsePacketSerializer::serializeResponse(stateRes);
		result.newHandler = m_handlerFactory->createMenuRequestHandler(*m_user);
	}
	catch (std::exception e)//If serialization failed the error will be serialized instead
	{
		result.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return result;
}
