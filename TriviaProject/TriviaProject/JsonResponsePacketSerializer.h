#pragma once
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
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
		static std::vector<char> serializeResponse(ErrorResponse response);
		static std::vector<char> serializeResponse(LoginResponse response);
		static std::vector<char> serializeResponse(SignupResponse response);
};