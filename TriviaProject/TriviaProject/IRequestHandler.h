#pragma once
#include <vector>





class IRequestHandler
{
public:
	bool isRequestRelevant(struct RequestInfo ri);
	struct RequestResult handleRequest(struct RequestInfo ri);

};


struct RequestResult
{
	char* response;
	IRequestHandler* newHandler;
};


struct RequestInfo
{
	int id;
	char* recievelTime;
	std::vector<char> buffer;

};
