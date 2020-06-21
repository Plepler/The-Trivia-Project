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
			"CREATE TABLE \"questions\" (\"data\"	TEXT NOT NULL,\"correct\"	TEXT NOT NULL,\"ans1\"	TEXT NOT NULL,\"ans2\"	TEXT NOT NULL,\"ans3\"	TEXT NOT NULL,\"id\"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT);"
			"CREATE TABLE \"Statistics\" (\"UserName\"	TEXT NOT NULL,\"AvarageAnswerTime\"	REAL NOT NULL,\"CorrectAnswers\"	INTEGER NOT NULL,\"Answers\"	INTEGER NOT NULL,\"Games\"	INTEGER NOT NULL,\"Score\"	INTEGER NOT NULL, PRIMARY KEY(\"USERNAME\"));";
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

float SqliteDataBase::getPlayerAvarageAnswerTime(std::string username)
{
	float ans = 0;
	selectBy("STATISTICS", "USERNAME " "= \"" + username + "\"", "AvarageAnswerTime", this->dataBase);
	ans = stof(dataHolder[0]);
	dataHolder.clear();
	return ans;
}

int SqliteDataBase::getNumOfCorrectAnswers(std::string username)
{
	int ans = 0;
	selectBy("STATISTICS", "USERNAME " "= \"" + username + "\"", "CorrectAnswers", this->dataBase);
	ans = stoi(dataHolder[0]);
	dataHolder.clear();
	return ans;
}

int SqliteDataBase::getNumOfTotalAnswers(std::string username)
{
	int ans = 0;
	selectBy("STATISTICS", "USERNAME " "= \"" + username + "\"", "Answers", this->dataBase);
	ans = stoi(dataHolder[0]);
	dataHolder.clear();
	return ans;
}

int SqliteDataBase::getNumOfPlayerGames(std::string username)
{
	int ans = 0;
	selectBy("STATISTICS", "USERNAME " "= \"" + username + "\"", "Games", this->dataBase);
	ans = stoi(dataHolder[0]);
	dataHolder.clear();
	return ans;
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
	selectBy("USERS","USERNAME " "= \""+ name +"\"", "USERNAME", this->dataBase);
	insertTo("STATISTICS", "(UserName, AvarageAnswerTime, CorrectAnswers, Answers, Games, Score)", "(\"" + dataHolder[0] + "\"" + ",0,0,0,0,0)", this->dataBase);
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

void SqliteDataBase::updateScore(std::string username, unsigned int timeToAnswer, unsigned int timePerQuestion)
{
	int Score = calcScore(username, timeToAnswer, timePerQuestion);
	updateBy("STATISTICS", "USERNAME = \"" + username + "\"", "Score" , std::to_string(Score), this->dataBase);
}

int SqliteDataBase::calcScore(std::string username, unsigned int timeToAnswer, unsigned int timePerQuestion)
{
	int addedScore = std::ceil(SCORE_PER_ANS * (1 - (timeToAnswer / (float)timePerQuestion)));
	selectBy("STATISTICS", "USERNAME = \"" + username + "\"", "Score", this->dataBase);
	int originScore = stoi(dataHolder[0]);
	dataHolder.clear();
	return addedScore + originScore;
}

/*
the function add all the questions to the database
input: NONE
output: NONE
*/
void SqliteDataBase::addQuestions()
{
	int option1 = 0, option2 = 0, option3 = 0;
	const std::string questions[AMOUND_OF_QUESTIONS] = {Q1 ,Q2 ,Q3 ,Q4 ,Q5 ,Q6 ,Q7 ,Q8 ,Q9 ,Q10};
	const std::string answers[AMOUND_OF_QUESTIONS] = {ANS1, ANS2, ANS3, ANS4, ANS5, ANS6, ANS7, ANS8, ANS9, ANS10};
	const std::string falseAnswers[AMOUND_OF_QUESTIONS][AMOUND_OF_WRONG_ANS] = { {F1, F2, F3}, {F4, F5, F6}, {F7, F8, F9}, {F10, F11, F12}, {F13, F14, F15}, {F16, F17, F18}, {F19, F20, F21}, {F22, F23, F24}, {F25, F26, F27}, {F28, F29, F30} };
	for (size_t i = 0; i < AMOUND_OF_QUESTIONS; i++)
	{	
		insertTo(QUESTION_TABLE, QUESTION_HEADERS, "(\"" + questions[i] + "\", \"" + answers[i] + "\", \"" + falseAnswers[i][0] + "\", \"" + falseAnswers[i][1] + "\", \"" + falseAnswers[i][2] + "\")", this->dataBase);
	}
	
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

void SqliteDataBase::updateBy(std::string src, std::string byWhat, std::string whatCulomn, std::string newValue, sqlite3* db)
{
	char* sqlite3_errmsg = nullptr;
	std::string SQL = "UPDATE "+ src + " SET " + whatCulomn + " = \"" + newValue + "\" WHERE " + byWhat + ";";

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
