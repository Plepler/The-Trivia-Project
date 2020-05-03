#pragma once
#include "IRequestHandler.h"
#include <string>

enum CODES{LOGIN = 100, SIGNUP};

class LoginRequestHandler : public IRequestHandler
{
public:

	virtual bool isRequestRelevant(struct RequestInfo ri);
	virtual struct RequestResult handleRequest(struct RequestInfo ri);

};