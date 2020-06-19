#include "JsonRequestPacketDeserializer.h"

using namespace nlohmann;

//bytes == unsigned char


/*ALL DESERIALIZER FUNCTIONS

These functions get a buffer of bytes
they turn the bytes into JSON type object
lastly they build the request struct with the JSON object.

In: The bytes buffer
Out: The same type request
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

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<unsigned char> buffer)
{
	GetPlayersInRoomRequest getPlayerReq;
	json j = json::parse(buffer);//Firsly rescue the json format from the bytes

	//Create a struct from the json
	getPlayerReq = { j["roomId"].get<unsigned int>()};

	return getPlayerReq;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> buffer)
{
	JoinRoomRequest joinReq;
	json j = json::parse(buffer);//Firsly rescue the json format from the bytes

	//Create a struct from the json
	joinReq = { j["roomId"].get<unsigned int>() };

	return joinReq;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> buffer)
{
	CreateRoomRequest createRoomReq;
	json j = json::parse(buffer);//Firsly rescue the json format from the bytes

	//Create a struct from the json
	createRoomReq = {

			j["roomName"].get<std::string>(),
			j["maxUsers"].get<unsigned int>(),
			j["questionCount"].get<unsigned int>(),
			j["answerTimeout"].get<unsigned int>()
	};

	return createRoomReq;
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