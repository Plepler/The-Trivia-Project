#include "SqliteDataBase.h"

//C'Tor
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

		std::string sql = "CREATE TABLE \"USERS\" (\"USERNAME\"	TEXT NOT NULL,\"PASSWORD\"	TEXT NOT NULL,\"EMAIL\"	TEXT NOT NULL,PRIMARY KEY(\"USERNAME\"));"
			"CREATE TABLE \"questions\" (\"data\"	TEXT NOT NULL,\"correct\"	TEXT NOT NULL,\"asn1\"	TEXT NOT NULL,\"ans2\"	TEXT NOT NULL,\"asn3\"	TEXT NOT NULL,\"id\"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT);";
		res = sqlite3_exec(dataBase, sql.c_str(), nullptr, nullptr, &sqlite3_errmsg);
		this->addQuestions();

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
float SqliteDataBase::getPlayerAvarageAnswerTime(std::string)
{
	return 0.0f;
}
int SqliteDataBase::getNumOfCorrectAnswers(std::string)
{
	return 0;
}
int SqliteDataBase::getNumOfTotalAnswers(std::string)
{
	return 0;
}
int SqliteDataBase::getNumOfPlayerGames(std::string)
{
	return 0;
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
bool SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
	bool ans = true;
	selectBy("USERS", "PASSWORD = \"" + password + "\"", "USERNAME", this->dataBase); // get the username that matchs to the password.
	if (dataHolder.size() == 0) { ans = false; } //if there is no data, that means there is no such user
	dataHolder.clear(); // clear the dataholder
	return ans;
}

void SqliteDataBase::addNewUser(std::string name, std::string password, std::string email)
{
	insertTo("USERS", "(USERNAME, PASSWORD, EMAIL)", "(\"" + name + "\", " + "\"" + password + "\", " + "\"" + email + "\")", this->dataBase);
	dataHolder.clear(); // clear the dataholder
}

std::list<Questions> SqliteDataBase::getQuestions(int amount)
{
	std::list<Questions> questions = std::list<Questions>();
	int i = 1;
	for (i = 1; i <= amount; i++)
	{
		selectBy("questions", "data AND correct", "ID = " + i, this->dataBase); 
		questions.push_back(Questions{ dataHolder[0], dataHolder[1]});
		dataHolder.clear();
	}
	return questions;
}

/*
the function add all the questions to the database
input: NONE
output: NONE
*/
void SqliteDataBase::addQuestions()
{
	insertTo(QUESTION_TABLE, QUESTION_HEADERS, "\"" + std::string(QUESTION1) + "\" AND \"" + ANS1 + "\" AND \"" + ANS5 + "\" AND \"" + ANS2 + "\" AND \"" + ANS9 "\"", this->dataBase);
	insertTo(QUESTION_TABLE, QUESTION_HEADERS, "\"" + std::string(QUESTION2) + "\" AND \"" + ANS2 + "\" AND \"" + ANS6 + "\" AND \"" + ANS1 + "\" AND \"" + ANS10 "\"", this->dataBase);
	insertTo(QUESTION_TABLE, QUESTION_HEADERS, "\"" + std::string(QUESTION3) + "\" AND \"" + ANS3 + "\" AND \"" + ANS2 + "\" AND \"" + ANS9 + "\" AND \"" + ANS5 "\"", this->dataBase);
	insertTo(QUESTION_TABLE, QUESTION_HEADERS, "\"" + std::string(QUESTION4) + "\" AND \"" + ANS4 + "\" AND \"" + ANS3 + "\" AND \"" + ANS6 + "\" AND \"" + ANS8 "\"", this->dataBase);
	insertTo(QUESTION_TABLE, QUESTION_HEADERS, "\"" + std::string(QUESTION5) + "\" AND \"" + ANS5 + "\" AND \"" + ANS4 + "\" AND \"" + ANS2 + "\" AND \"" + ANS10 "\"", this->dataBase);
	insertTo(QUESTION_TABLE, QUESTION_HEADERS, "\"" + std::string(QUESTION6) + "\" AND \"" + ANS6 + "\" AND \"" + ANS5 + "\" AND \"" + ANS1 + "\" AND \"" + ANS3 "\"", this->dataBase);
	insertTo(QUESTION_TABLE, QUESTION_HEADERS, "\"" + std::string(QUESTION7) + "\" AND \"" + ANS7 + "\" AND \"" + ANS9 + "\" AND \"" + ANS8 + "\" AND \"" + ANS4 "\"", this->dataBase);
	insertTo(QUESTION_TABLE, QUESTION_HEADERS, "\"" + std::string(QUESTION8) + "\" AND \"" + ANS8 + "\" AND \"" + ANS7 + "\" AND \"" + ANS5 + "\" AND \"" + ANS1 "\"", this->dataBase);
	insertTo(QUESTION_TABLE, QUESTION_HEADERS, "\"" + std::string(QUESTION9) + "\" AND \"" + ANS9 + "\" AND \"" + ANS8 + "\" AND \"" + ANS10 + "\" AND \"" + ANS3 "\"", this->dataBase);
	insertTo(QUESTION_TABLE, QUESTION_HEADERS, "\"" + std::string(QUESTION10) + "\" AND \"" + ANS10 + "\" AND \"" + ANS5 + "\" AND \"" + ANS7 + "\" AND \"" + ANS9 "\"", this->dataBase);
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
