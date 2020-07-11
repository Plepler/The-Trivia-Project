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
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);

private:
	Room m_room;
	LoggedUser m_user;
	RequestHandlerFactory* requestHandlerFactory;

	RequestResult leaveRoom(RequestInfo request);
	RequestResult getRoomState(RequestInfo request);

};