#pragma once
#include "LoggedUser.h"
#include <iostream>
#include <io.h>
#include <vector>
#include <exception>

class IDataBase 
{

public:
	virtual bool doseUserExist(std::string name) = 0;
	virtual bool doesPasswordMatch(std::string name, std::string password) = 0;
	virtual void addNewUser(std::string name, std::string password, std::string email) = 0;


	virtual bool open()  = 0;
	virtual void close() = 0;
	virtual void clear() = 0;


};