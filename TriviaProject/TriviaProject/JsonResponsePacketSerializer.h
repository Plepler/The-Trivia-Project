#pragma once
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>

#define BYTE2 1
#define BYTE3 2
#define BYTE4 3
#define BYTE5 4
#define LSH24 24
#define LSH16 16
#define LSH8 8
#define HEX_BYTE 0xFF

enum CODES { ERROR=0, LOGIN = 100, SIGNUP, OK = 200 };

struct ErrorResponse
{
	std::string data;

}typedef ErrorResponse;

struct LoginResponse
{
	unsigned int status;

}typedef LoginResponse;

struct SignupResponse
{
	unsigned int status;

}typedef SignupResponse;

class JsonResponsePacketSerializer
{

public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse response);
	static std::vector<unsigned char> serializeResponse(LoginResponse response);
	static std::vector<unsigned char> serializeResponse(SignupResponse response);


private:
	static void lengthToBytes(std::vector<unsigned char>& buffer, int length);
		


};

