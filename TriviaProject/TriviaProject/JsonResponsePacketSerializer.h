#pragma once
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include "Room.h"

#define BYTE2 1
#define BYTE3 2
#define BYTE4 3
#define BYTE5 4
#define LSH24 24
#define LSH16 16
#define LSH8 8
#define HEX_BYTE 0xFF

enum CODES { ERROR=0, LOGIN = 100, SIGNUP, LOGOUT, OK = 200, GET_ROOM, GET_PLAYER, STATS, JOIN, CREATE };

//Response structs

//Error response
struct ErrorResponse
{
	std::string data;

}typedef ErrorResponse;

//Login responses
struct LoginResponse
{
	unsigned int status;

}typedef LoginResponse;

struct SignupResponse
{
	unsigned int status;

}typedef SignupResponse;

struct LogoutResponse
{
	unsigned int status;

}typedef LogoutResponse;

//Room responses
struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;

}typedef GetRoomsResponse;

struct GetPlayersInRoomResponse
{
	std::vector<std::string> players;

}typedef GetPlayersInRoomResponse;

struct GetStatisticsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;

}typedef GetStatisticsResponse;

struct JoinRoomResponse
{
	unsigned int status;

}typedef JoinRoomResponse;

struct CreateRoomResponse
{
	unsigned int status;

}typedef CreateRoomResponse;


class JsonResponsePacketSerializer
{

public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse response);

	//Login response serialization
	static std::vector<unsigned char> serializeResponse(LoginResponse response);
	static std::vector<unsigned char> serializeResponse(SignupResponse response);

	//Room response serialization
	static std::vector<unsigned char> serializeResponse(LogoutResponse response);
	static std::vector<unsigned char> serializeResponse(GetRoomsResponse response);
	static std::vector<unsigned char> serializeResponse(GetPlayersInRoomResponse response);
	static std::vector<unsigned char> serializeResponse(JoinRoomResponse response);
	static std::vector<unsigned char> serializeResponse(CreateRoomResponse response);
	static std::vector<unsigned char> serializeResponse(GetStatisticsResponse response);


private:
	static void lengthToBytes(std::vector<unsigned char>& buffer, int length);

};

