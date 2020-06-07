#pragma once
#include "IDataBase.h"
#include "sqlite3.h"
#define QUESTION_TABLE "questions"
#define QUESTION_HEADERS "(\"data\", \"ans1\", \"ans2\", \"ans3\", \"correct\")"

#define QUESTION1 "Back to the 50', how much of the cornflakes indrustry was owend by kellogs?"
#define QUESTION2 "How ben gurion's rice was called?"
#define QUESTION3 "Who is sponsering 'peppsi'?"
#define QUESTION4 "How many pepole died during the coronavirus pandemic (part 1)?"
#define QUESTION5 "Because of what band the word 'heavy' was added to heavy metal"
#define QUESTION6 "What year was the very first model of the iPhone released?"
#define QUESTION7 "What percentage of the oxygen we breath is produced by plancton?"
#define QUESTION8 "What is the standart of FPS in new generation consoles?"
#define QUESTION9 "how much episodes the naruto series have (in total)?"
#define QUESTION10 "how to say ladybug in franch?"

#define ANS1 "50%"
#define ANS2 "ptitim"
#define ANS3 "messi"
#define ANS4 "6,000,000"
#define ANS5 "Iron butterfly"
#define ANS6 "2007"
#define ANS7 "70"
#define ANS8 "60"
#define ANS9 "720"
#define ANS10 "cockcinel" 

static std::vector<std::string> dataHolder;
int callBack(void* data, int argc, char** argv, char** azColName);


class SqliteDataBase : public IDataBase
{

public:
	SqliteDataBase();
	virtual bool doseUserExist(std::string name) override;
	virtual bool doesPasswordMatch(std::string password, std::string username) override;
	virtual void addNewUser(std::string name, std::string password, std::string email) override;
	virtual std::list<Questions> getQuestions(int amount);
	
	virtual bool open() override;
	virtual void close() override;
	virtual void clear() override;



private:
	sqlite3* dataBase;
	void addQuestions();
	void selectBy(std::string src, std::string byWhat, std::string what, sqlite3* db);
	void insertTo(std::string toWhere, std::string headers, std::string what, sqlite3* db);

};