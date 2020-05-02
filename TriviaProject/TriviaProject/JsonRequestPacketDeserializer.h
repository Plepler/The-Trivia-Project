#pragma once
#include <string>
class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(char* Buffer);
	static SignUpRequest deserializeSignupRequest(char* Buffer);


};


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