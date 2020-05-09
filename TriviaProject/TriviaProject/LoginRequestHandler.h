#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <string>

class RequestHandlerFactory;

enum CODES{LOGIN = 100, SIGNUP, OK = 200};

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(IDataBase* db);
	~LoginRequestHandler();
	virtual bool isRequestRelevant(RequestInfo ri);
	virtual RequestResult handleRequest(RequestInfo ri);
	

private:
	RequestHandlerFactory* m_handlerFactory;

	RequestResult login(RequestInfo ri);
	RequestResult signup(RequestInfo ri);

	//Helper functions
	void lengthToBytes(std::vector<unsigned char>& buffer, int length);

	template<typename T>
	void parseMsgToBytes(std::vector<unsigned char>& buffer, int code, T response);
};