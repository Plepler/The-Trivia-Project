#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room* room, LoggedUser* loggedUser, RequestHandlerFactory* hanlderFactory)
{
	m_room = room;
	m_user = loggedUser;
	m_handlerFactory = hanlderFactory;
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo request)
{
    bool flag = false;
    if(request.id == CLOSE || request.id == START || request.id == STATE)
    {
        flag = true;
    }
    return flag;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo request)
{
	RequestResult requestRes{ std::vector<unsigned char>(), nullptr };

	if (isRequestRelevant(request))
	{
		switch (request.id)
		{
		case CLOSE:
			requestRes = closeRoom(request);
			break;

		case START:
			requestRes = startGame(request);
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

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo request)
{
    return RequestResult();
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo request)
{
    return RequestResult();
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo request)
{
    return RequestResult();
}
