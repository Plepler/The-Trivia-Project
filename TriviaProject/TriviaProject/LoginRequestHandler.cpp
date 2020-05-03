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
	std::string rsp;
	if (isRequestRelevant(ri))
	{
		rsp = "{status: 1}";
		rr.response = std::vector<unsigned char>(rsp.begin(), rsp.end());
		rr.newHandler = nullptr;
	}
	else
	{
		rsp = "{message: \"ERROR\"}";
		rr.response = std::vector<unsigned char>(rsp.begin(), rsp.end());
		rr.newHandler = nullptr;
	}

	return rr;
}