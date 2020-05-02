#pragma once
#include <vector>

class IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo);
	RequestResult handleRequest(RequestInfo);
};


struct RequestResult
{
	char* response;
	IRequestHandler* newHandler;
}typedef RequestResult;


struct RequestInfo
{
	int id;
	char* recievelTime;
	std::vector<BYTE> buffer;

}typedef RequestInfo;