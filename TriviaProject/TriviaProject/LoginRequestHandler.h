#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

#include <string>
#include <mutex>

class RequestHandlerFactory;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;


class LoginRequestHandler : public IRequestHandler
{

public:
	LoginRequestHandler(IDataBase* db);
	~LoginRequestHandler();
	virtual bool isRequestRelevant(RequestInfo ri);
	virtual RequestResult handleRequest(RequestInfo ri);
	

private:
	RequestHandlerFactory* m_handlerFactory;

	RequestResult login(LoginRequest loginReq);
	RequestResult signup(SignUpRequest signupReq);

};