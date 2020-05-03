#include "JsonResponsePacketSerializer.h"
using namespace nlohmann;
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
	json data; std::vector<unsigned char> buffer;
	data["message"] = response.data;
	buffer = json::to_cbor(data);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
	json data; std::vector<unsigned char> buffer;
	data["status"] = response.status;
	buffer = json::to_cbor(data);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse response)
{
	json data; std::vector<unsigned char> buffer;
	data["status"] = response.status;
	buffer = json::to_cbor(data);
	return buffer;
}