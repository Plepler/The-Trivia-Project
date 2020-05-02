#pragma once
#include <string>



struct LoginRequest
{
	std::string username;
	std::string password;

}typedef LoginRequest;


struct SignUpRequest
{
	std::string username;
	std::string password;
	std::string email;

}typedef SignUpRequest;


class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(char* Buffer);
	static SignUpRequest deserializeSignupRequest(char* Buffer);


};

