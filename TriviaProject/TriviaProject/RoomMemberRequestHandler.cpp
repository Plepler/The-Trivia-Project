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
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo request)
{
	return RequestResult();
}
