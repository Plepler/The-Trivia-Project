#pragma once
#include <iostream>
class IDataBase {
public:
	virtual bool doseUserExist(std::string name) const = 0;
	virtual bool dosePasswordMatch(std::string name) const = 0;
	virtual void addNewUser(std::string name, std::string password, std::string email) const = 0;

};