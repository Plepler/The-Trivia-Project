#include "MenuRequestHandler.h"


MenuRequestHandler::MenuRequestHandler(LoggedUser user, RequestHandlerFactory* handlerFactory) : m_handlerFactory(handlerFactory), m_user(user)
{

}


/*
This function checks if the request is relevant 
to the current handler

In: request info (We need the id member)
Out: true if id is of relevant code type
*/
bool MenuRequestHandler::isRequestRelevant(RequestInfo request)
{
	bool flag = false;
	if (request.id == LOGOUT || request.id == GET_PLAYER || request.id == GET_ROOM || request.id == STATS || request.id == CREATE || request.id == JOIN)
	{
		flag = true;
	}
	return flag;
}



RequestResult MenuRequestHandler::handleRequest(RequestInfo reqInfo)
{
	std::vector<unsigned char> buffer;
	RequestResult requestRes;

	//Requests structs - Signout, getRooms and getStatistics dont require structs
	GetPlayersInRoomRequest getPlayersReq;
	JoinRoomRequest joinReq;
	CreateRoomRequest createReq;
	m_handlerFactory->createMenuRequestHandler(m_user);
	requestRes.newHandler = nullptr;

	if (isRequestRelevant(reqInfo))
	{
		switch (reqInfo.id)
		{
		case LOGOUT:
			requestRes = signout();
			break;

		case GET_PLAYER:
			getPlayersReq = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(reqInfo.buffer);
			requestRes = getPlayersInRoom(getPlayersReq);
			break;

		case GET_ROOM:
			requestRes = getRooms();
			break;

		case JOIN:
			joinReq = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(reqInfo.buffer);
			requestRes = joinRoom(joinReq);
			break;

		case CREATE:
			createReq = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(reqInfo.buffer);
			requestRes = createRoom(createReq);
			break;

		case STATS:
			requestRes = getStatistics();
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



RequestResult MenuRequestHandler::signout()
{
	return RequestResult();
}



RequestResult MenuRequestHandler::getRooms()
{
	RequestResult reqResult;
	GetRoomsResponse getRoomsRes;
	getRoomsRes.status = 1;
	try
	{
		getRoomsRes.rooms = m_handlerFactory->getRoomManager().getRooms();
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(getRoomsRes);
		reqResult.newHandler = nullptr;
	}
	catch (std::exception e)//If parameters failed the error will be serialized instead
	{
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return reqResult;
}

RequestResult MenuRequestHandler::getPlayersInRoom(GetPlayersInRoomRequest getPLayerReq)
{
	RequestResult reqResult;
	GetPlayersInRoomResponse getPlayersInRoomRes;

	try
	{
		//Get all users
		std::vector<LoggedUser> usersInRoom = m_handlerFactory->getRoomManager().getRoom(getPLayerReq.roomId).getAllUsers();
		//Get all usernames
		for (auto vecIter = usersInRoom.begin(); vecIter != usersInRoom.end(); vecIter++)
		{
			getPlayersInRoomRes.players.push_back((*vecIter).getUsername());
		}
		//Serialize answer
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(getPlayersInRoomRes);
		reqResult.newHandler = nullptr;
	}
	catch (std::exception e)//If parameters failed the error will be serialized instead
	{
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return reqResult;
}

RequestResult MenuRequestHandler::getStatistics()
{
	return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(JoinRoomRequest joinRoomReq)
{
	RequestResult reqResult;
	JoinRoomResponse joinRoomRes;
	
	try
	{
		joinRoomRes.status = 1;
		m_handlerFactory->getRoomManager().getRoom(joinRoomReq.roomId).addUser(m_user);
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(joinRoomRes);
		reqResult.newHandler = nullptr;
	}
	catch (std::exception e)//If parameters failed the error will be serialized instead
	{
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return reqResult;
}

RequestResult MenuRequestHandler::createRoom(CreateRoomRequest createRoomReq)
{
	RequestResult reqResult;
	JoinRoomResponse joinRoomRes;
	
	try
	{
		joinRoomRes.status = 1;
		//Call function to create room
		m_handlerFactory->getRoomManager().createRoom(createRoomReq.roomName, createRoomReq.maxUsers, createRoomReq.questionCount, createRoomReq.answerTimeout);
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(joinRoomRes);
		reqResult.newHandler = nullptr;
	}
	catch (std::exception e)//If parameters failed the error will be serialized instead
	{
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return reqResult;
}


