#pragma once
#include "IRequestHandler.h"
#include <string>

enum CODES{LOGIN = 100, SIGNUP, OK = 200};

class LoginRequestHandler : public IRequestHandler
{
public:

	virtual bool isRequestRelevant(struct RequestInfo ri);
	virtual struct RequestResult handleRequest(struct RequestInfo ri);


private:
	void lengthToBytes(std::vector<unsigned char>& buffer, int length);
	template<typename T>
	void parseMsgToBytes(std::vector<unsigned char>& buffer, int code, T response);
};