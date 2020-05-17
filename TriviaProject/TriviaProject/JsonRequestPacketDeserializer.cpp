#include "JsonRequestPacketDeserializer.h"

using namespace nlohmann;

//bytes == unsigned char

/*
This function turn a bytes buffer of a login request to a struct
In: The bytes buffer
Out: The login response
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	LoginRequest loginReq;
	json j = json::parse(buffer);//Firsly rescue the json format from the bytes
	
	//Create a struct from the json
	loginReq = {

			j["username"].get<std::string>(),
			j["password"].get<std::string>()
	};

	return loginReq;
}


/*
This function turn a bytes buffer of a sign up request to a struct
In: The bytes buffer
Out: The sign up response
*/
SignUpRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
	SignUpRequest signUpReq;
	json j = json::parse(buffer);//Firsly rescue the json format from the bytes
	
	//Create a struct from the json
	signUpReq = {

			j["username"].get<std::string>(),
			j["password"].get<std::string>(),
			j["email"].get<std::string>()
	};

	return signUpReq;
}



/*
Turn 4 bytes into a number
In: buffer (We use the first 4 bytes)
Out: decimal convertion of the 4 bytes
*/
int JsonRequestPacketDeserializer::bytesToLength(std::vector<unsigned char> buffer)
{
	return (int)(buffer[BYTE4] << LSH24 | buffer[BYTE3] << LSH16 | buffer[BYTE2] << LSH8 | buffer[BYTE1]);
}