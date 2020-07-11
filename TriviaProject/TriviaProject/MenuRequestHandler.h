#pragma once
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"

class RequestHandlerFactory;
class LoginRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser user, RequestHandlerFactory* handlerFactory);
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo reqInfo);


private:
	LoggedUser m_user;
	RequestHandlerFactory* m_handlerFactory;
	
	RequestResult signout(/*doesn't require request info*/);
	RequestResult getRooms(/*doesn't require request info*/);
	RequestResult getPlayersInRoom(GetPlayersInRoomRequest getPLayerReq);
	RequestResult getStatistics(/*doesn't require request info*/);
	RequestResult joinRoom(JoinRoomRequest joinRoomReq);
	RequestResult createRoom(CreateRoomRequest createRoomReq);

};