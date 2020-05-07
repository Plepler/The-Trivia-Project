#pragma once
#include <vector>
#include <ctime>
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#define LSH24 24
#define LSH16 16
#define LSH8 8
#define HEX_BYTE 0xFF

typedef struct RequestResult RequestResult;
typedef struct RequestInfo RequestInfo;

class IRequestHandler
{

public:
	virtual bool isRequestRelevant(RequestInfo ri) = 0;
	virtual RequestResult handleRequest(RequestInfo ri) = 0;

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

