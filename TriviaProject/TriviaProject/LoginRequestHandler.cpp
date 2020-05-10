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



RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo)
{
	std::vector<unsigned char> buffer;
	RequestResult requestRes;
	LoginRequest loginReq;
	SignUpRequest signupReq;
	m_handlerFactory->createLoginHandler();

	if (isRequestRelevant(reqInfo))
	{
		if (reqInfo.id == LOGIN)
		{
			loginReq = JsonRequestPacketDeserializer::deserializeLoginRequest(reqInfo.buffer);
			requestRes = login(loginReq);
		}
		else
		{
			signupReq = JsonRequestPacketDeserializer::deserializeSignupRequest(reqInfo.buffer);
			requestRes = signup(signupReq);
			requestRes.newHandler = nullptr;
		}
	}
	else
	{
		requestRes.response  = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{"Request doesnt Exist"});;
	}

	

	return requestRes;
}


RequestResult LoginRequestHandler::login(LoginRequest loginReq)
{
	RequestResult reqResult;
	LoginResponse loginRsp;
	loginRsp.status = 1;
	try
	{
		m_handlerFactory->getLoginManager().login(loginReq.username, loginReq.password);

		reqResult.response = JsonResponsePacketSerializer::serializeResponse(loginRsp);
	}
	catch (std::exception e)
	{
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return reqResult;
}

RequestResult LoginRequestHandler::signup(SignUpRequest signupReq)
{
	RequestResult reqResult;
	SignupResponse signupRsp;
	signupRsp.status = 1;

	try
	{
		m_handlerFactory->getLoginManager().signup(signupReq.username, signupReq.password, signupReq.email);
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(signupRsp);
	}
	catch (std::exception e)
	{
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return reqResult;
}





