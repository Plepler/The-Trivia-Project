#include "JsonResponsePacketSerializer.h"

using namespace nlohmann;

//Overriding the nlohmann fucntion to suit our RoomData struct
void from_json(const json& j, RoomData& val)
{
	j.at("id").get_to(val.id);
	j.at("name").get_to(val.name);
	j.at("maxPlayers").get_to(val.maxPlayers);
	j.at("timePerQuestion").get_to(val.timePerQuestion);
	j.at("isActive").get_to(val.isActive);
}
void to_json(json& j, const RoomData& val)
{
	j["id"] = val.id;
	j["name"] = val.name;
	j["maxPlayers"] = val.maxPlayers;
	j["timePerQuestion"] = val.timePerQuestion;
	j["isActive"] = val.isActive;
}



/*FOR ALL SERIALIZE FUNCTIONS!!!

These functions get a response and turn it into json format
then finally into a bytes buffer.

In addition it build the length and data type of the message.

In: The response (Error / login / signup)
Out: Bytes buffer of json format
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
	json data; 
	std::vector<unsigned char> buffer;
	std::vector<unsigned char> temp;
	std::string tempStr;

	buffer.push_back(ERROR);//add data type
	data["message"] = response.data;
	tempStr = data.dump();

	//add length of data
	lengthToBytes(buffer, tempStr.size());

	temp.insert(temp.begin(), tempStr.begin(), tempStr.end());
	buffer.insert(buffer.end(), temp.begin(), temp.end());
	return buffer;
}



std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
	json data;
	std::vector<unsigned char> buffer;
	std::vector<unsigned char> temp;
	std::string tempStr;

	//add data type
	buffer.push_back(LOGIN);
	data["status"] = response.status;
	tempStr = data.dump();

	//add length of data
	lengthToBytes(buffer, tempStr.size());

	//Copy string json into vector (temp) then append to buffer
	temp.insert(temp.begin(), tempStr.begin(), tempStr.end());
	buffer.insert(buffer.end(), temp.begin(), temp.end());
	return buffer;
}



std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse response)
{
	json data;
	std::vector<unsigned char> buffer;
	std::vector<unsigned char> temp;
	std::string tempStr;

	//add data type
	buffer.push_back(SIGNUP);
	data["status"] = response.status;
	tempStr = data.dump();

	//add length of data
	lengthToBytes(buffer, tempStr.size());

	//Copy string json into vector (temp) then append to buffer
	temp.insert(temp.begin(), tempStr.begin(), tempStr.end());
	buffer.insert(buffer.end(), temp.begin(), temp.end());
	return buffer;
}



std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse response)
{
	json data;
	std::vector<unsigned char> buffer;
	std::vector<unsigned char> temp;
	std::string tempStr;

	//add data type
	buffer.push_back(LOGOUT);
	data["status"] = response.status;
	tempStr = data.dump();

	//add length of data
	lengthToBytes(buffer, tempStr.size());

	//Copy string json into vector (temp) then append to buffer
	temp.insert(temp.begin(), tempStr.begin(), tempStr.end());
	buffer.insert(buffer.end(), temp.begin(), temp.end());
	return buffer;
}



std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse response)
{
	json data;

	std::vector<unsigned char> buffer;
	std::vector<unsigned char> temp;
	std::string tempStr;

	//add data type
	buffer.push_back(GET_ROOM);
	data["status"] = response.status;
	data["rooms"] = response.rooms;
	tempStr = data.dump();

	//add length of data
	lengthToBytes(buffer, tempStr.size());

	//Copy string json into vector (temp) then append to buffer
	temp.insert(temp.begin(), tempStr.begin(), tempStr.end());
	buffer.insert(buffer.end(), temp.begin(), temp.end());
	return buffer;
}



std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse response)
{
	json data;
	std::vector<unsigned char> buffer;
	std::vector<unsigned char> temp;
	std::string tempStr;

	//add data type
	buffer.push_back(GET_PLAYER);
	data["players"] = response.players;
	tempStr = data.dump();

	//add length of data
	lengthToBytes(buffer, tempStr.size());

	//Copy string json into vector (temp) then append to buffer
	temp.insert(temp.begin(), tempStr.begin(), tempStr.end());
	buffer.insert(buffer.end(), temp.begin(), temp.end());
	return buffer;
}



std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse response)
{
	json data;
	std::vector<unsigned char> buffer;
	std::vector<unsigned char> temp;
	std::string tempStr;

	//add data type
	buffer.push_back(JOIN);
	data["status"] = response.status;
	tempStr = data.dump();

	//add length of data
	lengthToBytes(buffer, tempStr.size());

	//Copy string json into vector (temp) then append to buffer
	temp.insert(temp.begin(), tempStr.begin(), tempStr.end());
	buffer.insert(buffer.end(), temp.begin(), temp.end());
	return buffer;
}



std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse response)
{
	json data;
	std::vector<unsigned char> buffer;
	std::vector<unsigned char> temp;
	std::string tempStr;

	//add data type
	buffer.push_back(CREATE);
	data["status"] = response.status;
	tempStr = data.dump();

	//add length of data
	lengthToBytes(buffer, tempStr.size());

	//Copy string json into vector (temp) then append to buffer
	temp.insert(temp.begin(), tempStr.begin(), tempStr.end());
	buffer.insert(buffer.end(), temp.begin(), temp.end());
	return buffer;
}



std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetStatisticsResponse response)
{
	json data;
	std::vector<unsigned char> buffer;
	std::vector<unsigned char> temp;
	std::string tempStr;

	//add data type
	buffer.push_back(STATS);
	data["status"] = response.status;
	data["statistics"] = response.statistics;
	tempStr = data.dump();

	//add length of data
	lengthToBytes(buffer, tempStr.size());

	//Copy string json into vector (temp) then append to buffer
	temp.insert(temp.begin(), tempStr.begin(), tempStr.end());
	buffer.insert(buffer.end(), temp.begin(), temp.end());
	return buffer;
}





/*
This funtion turn a number into a 4 bytes vector
In: buffer that will contain the number, the number
*/
void JsonResponsePacketSerializer::lengthToBytes(std::vector<unsigned char>& buffer, int length)
{
	buffer.push_back(length >> LSH24 & HEX_BYTE);
	buffer.push_back(length >> LSH16 & HEX_BYTE);
	buffer.push_back(length >> LSH8 & HEX_BYTE);
	buffer.push_back(length & HEX_BYTE);
}
