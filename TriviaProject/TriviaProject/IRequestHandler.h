#pragma once
#include <vector>
#include <ctime>




class IRequestHandler
{

public:
	virtual bool isRequestRelevant(struct RequestInfo ri) = 0;
	virtual struct RequestResult handleRequest(struct RequestInfo ri) = 0;

};


struct RequestResult
{
	std::vector<unsigned char> response;
	IRequestHandler* newHandler;
};


struct RequestInfo
{
	int id;
	time_t recievelTime;
	std::vector<unsigned char> buffer;

};
