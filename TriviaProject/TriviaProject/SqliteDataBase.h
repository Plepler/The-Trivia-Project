#pragma once
#include "IDataBase.h"
#include "sqlite3.h"


static std::vector<std::string> dataHolder;
int callBack(void* data, int argc, char** argv, char** azColName);


class SqliteDataBase : public IDataBase
{

public:
	virtual bool doseUserExist(std::string name) override;
	virtual bool doesPasswordMatch(std::string password, std::string username) override;
	virtual void addNewUser(std::string name, std::string password, std::string email) override;

	virtual bool open() override;
	virtual void close() override;
	virtual void clear() override;



private:
	sqlite3* dataBase;

	void selectBy(std::string src, std::string byWhat, std::string what, sqlite3* db);
	void insertTo(std::string toWhere, std::string headers, std::string what, sqlite3* db);

};