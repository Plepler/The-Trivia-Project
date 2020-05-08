#pragma once
#include "IDataBase.h"
#include "sqlite3.h"
#include <io.h>
#include <vector>
#include <exception>

static std::vector<std::string> dataHolder;
int callBack(void* data, int argc, char** argv, char** azColName);

class SqliteDataBase : IDataBase {
public:

	virtual bool doseUserExist(std::string name);
	virtual bool dosePasswordMatch(std::string password, std::string username);
	virtual void addNewUser(std::string name, std::string password, std::string email);

	bool open();
	void close();
	void clear();

private:
	sqlite3* dataBase;
};