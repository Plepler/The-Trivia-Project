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
