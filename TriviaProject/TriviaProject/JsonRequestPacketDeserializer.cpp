#include "JsonRequestPacketDeserializer.h"

using namespace nlohmann;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	LoginRequest loginReq;
	json j = json::parse(buffer);
	
	loginReq = {

			j["username"].get<std::string>(),
			j["password"].get<std::string>()
	};

	return loginReq;
}



SignUpRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
	SignUpRequest signUpReq;
	json j = json::parse(buffer);
	
	signUpReq = {

			j["username"].get<std::string>(),
			j["password"].get<std::string>(),
			j["email"].get<std::string>()
	};

	return signUpReq;
}


int JsonRequestPacketDeserializer::bytesToLength(std::vector<unsigned char> buffer)
{
	return (int)(buffer[BYTE4] << LSH24 | buffer[BYTE3] << LSH16 | buffer[BYTE2] << LSH8 | buffer[BYTE1]);
}