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

enum CODES { ERROR=0, LOGIN = 100, SIGNUP, LOGOUT, OK = 200, GET_ROOM, GET_PLAYER, STATS, JOIN, CREATE, CLOSE, START, STATE, LEAVE};

//Response structs

//Error response
struct ErrorResponse
{
	std::string message;

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

//v3.0.0
struct CloseRoomResponse
{
	unsigned int status;

}typedef CloseRoomResponse;

struct StartgameResponse
{
	unsigned int status;

}typedef StartgameResponse;

struct GetRoomStateResponse
{
	unsigned int status;
	bool HasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;

}typedef GetRoomStateResponse;

struct LeaveRoomResponse
{
	unsigned int status;

}typedef LeaveRoomResponse;

class JsonResponsePacketSerializer
{

public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse response);

	//Login response serialization
	static std::vector<unsigned char> serializeResponse(LoginResponse response);
	static std::vector<unsigned char> serializeResponse(SignupResponse response);

	//v2.0.0 Room response serialization
	static std::vector<unsigned char> serializeResponse(LogoutResponse response);
	static std::vector<unsigned char> serializeResponse(GetRoomsResponse response);
	static std::vector<unsigned char> serializeResponse(GetPlayersInRoomResponse response);
	static std::vector<unsigned char> serializeResponse(JoinRoomResponse response);
	static std::vector<unsigned char> serializeResponse(CreateRoomResponse response);
	static std::vector<unsigned char> serializeResponse(GetStatisticsResponse response);

	//v3.0.0 room response serialization
	static std::vector<unsigned char> serializeResponse(CloseRoomResponse response);
	static std::vector<unsigned char> serializeResponse(StartgameResponse response);
	static std::vector<unsigned char> serializeResponse(GetRoomStateResponse response);
	static std::vector<unsigned char> serializeResponse(LeaveRoomResponse response);

private:
	static void lengthToBytes(std::vector<unsigned char>& buffer, int length);

};

