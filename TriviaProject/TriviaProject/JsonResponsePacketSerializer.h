#pragma once
#include <iostream>
struct ErrorResponse
{
	std::string data;

}typedef ErrorResponse;

struct LoginResponse
{
	std::string data;

}typedef LoginResponse;

struct SignupResponse
{
	std::string data;

}typedef SignupResponse;

class JsonResponsePacketSerializer
{
	public:
		static char* serializeResponse(ErrorResponse error);
		static char* serializeResponse(LoginResponse error);
		static char* serializeResponse(SignupResponse error);
};