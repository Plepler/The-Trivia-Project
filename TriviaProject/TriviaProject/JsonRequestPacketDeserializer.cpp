#include "JsonRequestPacketDeserializer.h"

using namespace nlohmann;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	LoginRequest loginReq;
	json j;

	json::from_cbor(buffer);

	loginReq = {

			j["username"].get<std::string>(),
			j["password"].get<std::string>()
	};

	return loginReq;
}



SignUpRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
	SignUpRequest signUpReq;
	json j;


	json::from_cbor(buffer);
	
	signUpReq = {

			j["username"].get<std::string>(),
			j["password"].get<std::string>(),
			j["email"].get<std::string>()
	};

	return signUpReq;
}


int JsonRequestPacketDeserializer::bytesToLength(std::vector<unsigned char> buffer)
{
	return (int)(buffer[BYTE1] << LSH24 | buffer[BYTE2] << LSH16 | buffer[BYTE3] << LSH8 | buffer[BYTE4]);
}