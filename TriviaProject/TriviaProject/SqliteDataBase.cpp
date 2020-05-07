#include "SqliteDataBase.h"

bool SqliteDataBase::open()
{
	//try to open the file
	std::string dataBaseFileName = "Trivia.sqlite";
	int doesFileExist = _access(dataBaseFileName.c_str(), 0);
	int res = sqlite3_open(dataBaseFileName.c_str(), &this->dataBase);
	char* sqlite3_errmsg;
	//if the proc failed, print relevent msg.
	if (res != SQLITE_OK)
	{
		dataBase = nullptr;
		std::cout << "Failed to open dataBase" << std::endl;
		return false;
	}
	//if it dosent exist, create one
	if (doesFileExist != 0) {

		std::string sql = "CREATE TABLE \"USERS\" (\"USERNAME\"	TEXT NOT NULL,\"PASSWORD\"	TEXT NOT NULL,\"EMAIL\"	TEXT NOT NULL,PRIMARY KEY(\"PASSWORD\")); ";
		res = sqlite3_exec(dataBase, sql.c_str(), nullptr, nullptr, &sqlite3_errmsg);
	}
	dataHolder.clear();
	return true;
}

/*
the function close the database
input: NONE
output: NONE
*/
void SqliteDataBase::close()
{
	//clear and close all the vars.
	dataHolder.clear();
	sqlite3_close(this->dataBase);
	this->dataBase = nullptr;
}

/*
the function delete the database
input: NONE
output: NONE
*/
void SqliteDataBase::clear()
{
	//create the sql msg
	char* sqlite3_errmsg;
	dataHolder.clear();
	std::string sql = "DELETE FROM USERS;";
	//send it
	int res = sqlite3_exec(this->dataBase, sql.c_str(), nullptr, nullptr, &sqlite3_errmsg);
}

/*
the callback function that i used.
the function gets all the data from the data base and order it in a vector of strings, the vector is global
*/
int callBack(void* data, int argc, char** argv, char** azColName)
{
	int i = 0;
	for (i = 0; i < argc; i++)
	{
		dataHolder.push_back(argv[i]);
	}
	return 0;
}
