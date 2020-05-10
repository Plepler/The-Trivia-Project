#include "JsonResponsePacketSerializer.h"

using namespace nlohmann;

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
	json data; 
	std::vector<unsigned char> buffer;
	std::vector<unsigned char> temp;

	buffer.push_back(ERROR);
	lengthToBytes(buffer, response.data.size() + 10);

	data["message"] = response.data;

	temp = json::to_cbor(data);
	buffer.insert(buffer.end(), temp.begin(), temp.end());
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
	json data; 
	std::vector<unsigned char> buffer;
	std::vector<unsigned char> temp;

	data["status"] = response.status;

	buffer.push_back(LOGIN);
	lengthToBytes(buffer, data.size());

	temp = json::to_cbor(data);
	buffer.insert(buffer.end(), temp.begin(), temp.end());
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse response)
{
	json data;
	std::vector<unsigned char> buffer;
	std::vector<unsigned char> temp;

	data["status"] = response.status;

	buffer.push_back(SIGNUP);
	lengthToBytes(buffer, data.size());

	temp = json::to_cbor(data);
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
