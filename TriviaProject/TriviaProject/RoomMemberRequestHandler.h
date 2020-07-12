#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"

class RequestHandlerFactory;
class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(Room* room, LoggedUser* loggedUser, RequestHandlerFactory* hanlderFactory);

	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);

private:
	Room* m_room;
	LoggedUser* m_user;
	RequestHandlerFactory* m_handlerFactory;

	RequestResult leaveRoom(RequestInfo request);
	RequestResult getRoomState(RequestInfo request);

};