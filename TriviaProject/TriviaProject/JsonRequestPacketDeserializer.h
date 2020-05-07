#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>


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
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static SignUpRequest deserializeSignupRequest(std::vector<unsigned char> buffer);


};

