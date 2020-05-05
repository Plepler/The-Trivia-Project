#include "LoginRequestHandler.h"


bool LoginRequestHandler::isRequestRelevant(struct RequestInfo ri)
{
	bool flag = false;
	if (ri.id == LOGIN || ri.id == SIGNUP)
	{
		flag = true;
	}
	return false;
}



struct RequestResult LoginRequestHandler::handleRequest(struct RequestInfo ri)
{
	struct RequestResult rr;
	

	ErrorResponse errorRsp = {"ERROR"};
	LoginResponse loginRsp = { 1 };
	SignupResponse signupRsp = { 1 };

	if (isRequestRelevant(ri))
	{
		//Right now will always send goood response
		if (ri.id == LOGIN)
		{
			rr.response = JsonResponsePacketSerializer::serializeResponse(loginRsp);
		}
		else
		{
			rr.response = JsonResponsePacketSerializer::serializeResponse(signupRsp);
		}
		
		rr.newHandler = nullptr;
	}
	else
	{
		rr.response = rr.response = JsonResponsePacketSerializer::serializeResponse(errorRsp);;
		rr.newHandler = nullptr;
	}

	return rr;
}