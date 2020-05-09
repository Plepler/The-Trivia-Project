#include "LoginRequestHandler.h"




LoginRequestHandler::LoginRequestHandler(IDataBase * db) : IRequestHandler(), m_handlerFactory(new RequestHandlerFactory(db))
{

}

LoginRequestHandler::~LoginRequestHandler()
{

}


bool LoginRequestHandler::isRequestRelevant(RequestInfo ri)
{
	bool flag = false;
	if (ri.id == LOGIN || ri.id == SIGNUP)
	{
		flag = true;
	}
	return flag;
}



RequestResult LoginRequestHandler::handleRequest(RequestInfo ri)
{
	struct RequestResult rr;
	

	ErrorResponse errorRsp = {"ERROR"};
	LoginResponse loginRsp = { 1 };
	SignupResponse signupRsp = { 1 };

	if (isRequestRelevant(ri))
	{
		rr.newHandler = nullptr;
		//Right now will always send goood response
		if (ri.id == LOGIN)
		{
			parseMsgToBytes(rr.response, OK, loginRsp);
		}
		else
		{
			parseMsgToBytes(rr.response, OK, signupRsp);
		}

		
	}
	else
	{
		rr.response = rr.response = JsonResponsePacketSerializer::serializeResponse(errorRsp);;
		rr.newHandler = nullptr;
	}

	return rr;
}


RequestResult LoginRequestHandler::login(RequestInfo ri)
{
	return RequestResult{};
}

RequestResult LoginRequestHandler::signup(RequestInfo ri)
{
	return RequestResult{};
}




template<typename T>
void LoginRequestHandler::parseMsgToBytes(std::vector<unsigned char>& buffer, int code, T response)
{
	int length = 0;
	buffer = JsonResponsePacketSerializer::serializeResponse(response);
	length = buffer.size();
	lengthToBytes(buffer, length);
	buffer.insert(buffer.begin(), code);

}


void LoginRequestHandler::lengthToBytes(std::vector<unsigned char>& buffer, int length)
{
	buffer.insert(buffer.begin(), length >> LSH24 & HEX_BYTE);
	buffer.insert(buffer.begin(), length >> LSH16 & HEX_BYTE);
	buffer.insert(buffer.begin(), length >> LSH8 & HEX_BYTE);
	buffer.insert(buffer.begin(), length & HEX_BYTE);
}