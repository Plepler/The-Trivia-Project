#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#define BYTE1 0
#define BYTE2 1
#define BYTE3 2
#define BYTE4 3
#define LSH24 24
#define LSH16 16
#define LSH8 8
#define HEX_BYTE 0xFF


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

struct GetPlayersInRoomRequest
{
	unsigned int roomId;

}typedef GetPlayersInRoomRequest;


struct JoinRoomRequest
{
	unsigned int roomId;

}typedef JoinRoomRequest;


struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;

}typedef CreateRoomRequest;





class JsonRequestPacketDeserializer
{
public:
	//Login requests
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static SignUpRequest deserializeSignupRequest(std::vector<unsigned char> buffer);

	//Room requests
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<unsigned char> buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char> buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char> buffer); 

	static int bytesToLength(std::vector<unsigned char> buffer);

};

