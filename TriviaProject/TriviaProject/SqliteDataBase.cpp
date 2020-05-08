#include "SqliteDataBase.h"

SqliteDataBase::SqliteDataBase()
{
	dataBase = nullptr;
}

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

		std::string sql = "CREATE TABLE \"USERS\" (\"USERNAME\"	TEXT NOT NULL,\"PASSWORD\"	TEXT NOT NULL,\"EMAIL\"	TEXT NOT NULL,PRIMARY KEY(\"USERNAME\")); ";
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
 the function check if user exist in the database
 input: the name to check
 output: trur ot false.
 */
bool SqliteDataBase::doseUserExist(std::string name)
{
	bool ans = true; //declaer
	selectBy("USERS", "USERNAME = \"" + name + "\"", "USERNAME", this->dataBase); // get the username that matchs.
	if (dataHolder.size() == 0) {ans = false;} //if there is no data, that means there is no such user
	dataHolder.clear();// clear the dataholder
	return ans;

}
bool SqliteDataBase::doesPasswordMatch(std::string password, std::string username)
{
	bool ans = true;
	selectBy("USERS", "PASSWORD = \"" + password + "\"", "USERNAME", this->dataBase); // get the username that matchs to the password.
	if (dataHolder.size() == 0) { ans = false; } //if there is no data, that means there is no such user
	dataHolder.clear(); // clear the dataholder
	return ans;
}

void SqliteDataBase::addNewUser(std::string name, std::string password, std::string email)
{
	insertTo("USERS", "(USERNAME, PASSWORD, EMAIL)", "(\"" + name + "\"" + "\"" + password + "\"" + "\"" + email + "\")", this->dataBase);
	dataHolder.clear(); // clear the dataholder
}

/*
the function send a select sql request based on the parameters that given
input : src - from which table to select
bywhat - by what conditions to select
what - what to get from the data base
db - the database to get from
output : NONE
*/
void SqliteDataBase::selectBy(std::string src, std::string byWhat, std::string what, sqlite3* db)
{
	char* sqlite3_errmsg = nullptr;
	std::string SQL = "SELECT " + what + " FROM " + src + " WHERE " + byWhat + ";";
	int res = sqlite3_exec(db, SQL.c_str(), callBack, nullptr, &sqlite3_errmsg);
	if (sqlite3_errmsg != nullptr)
	{
		std::cout << std::string(sqlite3_errmsg) << std::endl;
	}

}

/*
the function send an insert sql request based on the parameters that given
input : src - to which table to insert
bywhat - by what conditions to insert
what - what to insert from the data base
db - the database to insert to
output : NONE
*/
void SqliteDataBase::insertTo(std::string toWhere, std::string headers, std::string what, sqlite3* db)
{
	char* sqlite3_errmsg = nullptr;
	std::string SQL = "INSERT INTO " + toWhere + " " + headers + " VALUES " + what + ";";

	int res = sqlite3_exec(db, SQL.c_str(), nullptr, nullptr, &sqlite3_errmsg);
	if (sqlite3_errmsg != nullptr)
	{
		std::cout << std::string(sqlite3_errmsg) << std::endl;
	}
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
