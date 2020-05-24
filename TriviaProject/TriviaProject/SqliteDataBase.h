#pragma once
#include "IDataBase.h"
#include "sqlite3.h"
#define QUESTION_TABLE "questions"
#define QUESTION_HEADERS "(\"data\", \"ans1\", \"ans2\", \"ans3\", \"correct\")"

#define QUESTION1 ""
#define QUESTION2 ""
#define QUESTION3 ""
#define QUESTION4 ""
#define QUESTION5 ""
#define QUESTION6 ""
#define QUESTION7 ""
#define QUESTION8 ""
#define QUESTION9 ""
#define QUESTION10 ""

#define ANS1 ""
#define ANS2 ""
#define ANS3 ""
#define ANS4 ""
#define ANS5 ""
#define ANS6 ""
#define ANS7 ""
#define ANS8 ""
#define ANS9 ""
#define ANS10 "" 

static std::vector<std::string> dataHolder;
int callBack(void* data, int argc, char** argv, char** azColName);


class SqliteDataBase : public IDataBase
{

public:
	SqliteDataBase();
	virtual bool doseUserExist(std::string name) override;
	virtual bool doesPasswordMatch(std::string password, std::string username) override;
	virtual void addNewUser(std::string name, std::string password, std::string email) override;
	virtual std::list<Questions> getQuestions(int Id);
	virtual bool open() override;
	virtual void close() override;
	virtual void clear() override;



private:
	sqlite3* dataBase;
	void addQuestions();
	void selectBy(std::string src, std::string byWhat, std::string what, sqlite3* db);
	void insertTo(std::string toWhere, std::string headers, std::string what, sqlite3* db);

};