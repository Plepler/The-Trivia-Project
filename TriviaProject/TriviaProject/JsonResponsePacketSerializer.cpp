#include "JsonResponsePacketSerializer.h"

using namespace nlohmann;

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
	json data; 
	std::vector<unsigned char> buffer;
	std::vector<unsigned char> temp;
	std::string tempStr;

	buffer.push_back(ERROR);
	data["message"] = response.data;
	tempStr = data.dump();

	//Length of data
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

	buffer.push_back(ERROR);

	data["status"] = response.status;
	tempStr = data.dump();

	lengthToBytes(buffer, tempStr.size());

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

	buffer.push_back(ERROR);


	data["status"] = response.status;
	tempStr = data.dump();

	lengthToBytes(buffer, tempStr.size());

	temp.insert(temp.begin(), tempStr.begin(), tempStr.end());
	buffer.insert(buffer.end(), temp.begin(), temp.end());
	return buffer;
}

void JsonResponsePacketSerializer::lengthToBytes(std::vector<unsigned char>& buffer, int length)
{
	buffer.push_back(length >> LSH24 & HEX_BYTE);
	buffer.push_back(length >> LSH16 & HEX_BYTE);
	buffer.push_back(length >> LSH8 & HEX_BYTE);
	buffer.push_back(length & HEX_BYTE);
	
}
