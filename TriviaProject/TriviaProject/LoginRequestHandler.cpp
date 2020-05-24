#include "LoginRequestHandler.h"


std::mutex database_mutex;

//C'Tor. doesn't create database just passes him forward.
LoginRequestHandler::LoginRequestHandler(IDataBase * db) : IRequestHandler(), m_handlerFactory(new RequestHandlerFactory(db))
{

}

//D'Tor
LoginRequestHandler::~LoginRequestHandler()
{

}



/*
Check if data type is of login /sign up requests
In: the request info
Out: true if relevant
*/
bool LoginRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
	bool flag = false;
	if (reqInfo.id == LOGIN || reqInfo.id == SIGNUP || reqInfo.id == ERROR)
	{
		flag = true;
	}
	return flag;
}



/*
This function handles the login / signup requests. 
it will desirelize the data, contact the database
and finally serlieze an apropriate response

In: The request info
Out: The results of the request
*/
RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo)
{
	std::vector<unsigned char> buffer;
	RequestResult requestRes;
	LoginRequest loginReq;
	SignUpRequest signupReq;
	m_handlerFactory->createLoginHandler();
	requestRes.newHandler = nullptr;

	if (isRequestRelevant(reqInfo))
	{
		
		switch (reqInfo.id)
		{
		case LOGIN:
			loginReq = JsonRequestPacketDeserializer::deserializeLoginRequest(reqInfo.buffer);
			database_mutex.lock();
			requestRes = login(loginReq);//Contact database
			database_mutex.unlock();
			break;

		case SIGNUP:
			signupReq = JsonRequestPacketDeserializer::deserializeSignupRequest(reqInfo.buffer);
			database_mutex.lock();
			requestRes = signup(signupReq);//Contact database
			database_mutex.unlock();
			break;

		default:
			requestRes.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ "Already logged in" });
			break;
		}
	}
	else
	{
		//If excpetions are thrown about the request type they will be caught here
		requestRes.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{"Request doesnt Exist"});
	}

	return requestRes;
}



/*
This function will deserialze an login request and serialize an answer
In: the login request struct
*/
RequestResult LoginRequestHandler::login(LoginRequest loginReq)
{
	RequestResult reqResult;
	LoginResponse loginRsp;
	loginRsp.status = 1;
	try
	{
		m_handlerFactory->getLoginManager().login(loginReq.username, loginReq.password);
		reqResult.response =  JsonResponsePacketSerializer::serializeResponse(loginRsp);
		reqResult.newHandler = new MenuRequestHandler(LoggedUser("1"), m_handlerFactory);
	}
	catch (std::exception e)//If parameters failed the error will be serialized instead
	{
		reqResult.response =  JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return reqResult;
}

/*
This function will deserialze an sign up request and serialize an answer
In: the sign up request struct
*/
RequestResult LoginRequestHandler::signup(SignUpRequest signupReq)
{
	RequestResult reqResult;
	SignupResponse signupRsp;
	signupRsp.status = 1;

	try
	{
		m_handlerFactory->getLoginManager().signup(signupReq.username, signupReq.password, signupReq.email);
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(signupRsp);
		reqResult.newHandler = new MenuRequestHandler(LoggedUser("1"), m_handlerFactory);
	}
	catch (std::exception e)//If parameters failed the error will be serialized instead
	{
		reqResult.response = JsonResponsePacketSerializer::serializeResponse(ErrorResponse{ e.what() });
	}

	return reqResult;
}





