#pragma once
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo request);
	RequestResult handleRequest(RequestInfo request);


private:
	LoggedUser m_user;
	RequestHandlerFactory m_handlerFactory;

	RequestResult signout(/*Request*/);
	RequestResult getRooms();
	RequestResult getPlayersInRoom(GetPlayersInRoomRequest getPLayerReq);
	RequestResult getStatistics(/*Request*/); 
	RequestResult joinRoom(JoinRoomRequest joinRoomReq);
	RequestResult createRoom(CreateRoomRequest createRoomReq);

};