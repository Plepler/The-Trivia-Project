#pragma once
#include "IDataBase.h"
#include "sqlite3.h"
#include <cstdlib>

#define QUESTION_TABLE "questions"
#define QUESTION_HEADERS "(\"data\", \"correct\", \"ans1\", \"ans2\", \"ans3\")"
#define AMOUND_OF_QUESTIONS 10
#define AMOUND_OF_WRONG_ANS 3
#define Q1 "Back to the 50', how much of the cornflakes indrustry was owend by kellogs?"
#define Q2 "How ben gurion's rice was called?"
#define Q3 "Who is sponsering 'peppsi'?"
#define Q4 "How many pepole got sick during the coronavirus pandemic (part 1)?"
#define Q5 "Because of what band the word 'heavy' was added to heavy metal"
#define Q6 "What year was the very first model of the iPhone released?"
#define Q7 "What percentage of the oxygen we breath is produced by plancton?"
#define Q8 "What is the standart of FPS in new generation consoles?"
#define Q9 "how much episodes the naruto series have (in total)?"
#define Q10 "how to say ladybug in french?"

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

#define F1 "40%"
#define F2 "80%" 
#define F3 "30%"

#define F4 "zion rice"
#define F5 "pasta"
#define F6 "rice"

#define F7 "Ronaldo"
#define F8 "brad pit"
#define F9 "mia kalifa"

#define F10 "5,000,000" 
#define F11 "2,000,000"
#define F12 "13,000,000"

#define F13 "metalica"
#define F14 "led zepelin"
#define F15 "bring me the horizon"

#define F16 "2005"
#define F17 "2010"
#define F18 "1999"

#define F19 "30%"
#define F20 "10%" 
#define F21 "50%"

#define F22 "144"
#define F23 "30"
#define F24 "there is no standard"

#define F25 "220"
#define F26 "500"
#define F27 "430"

#define F28 "fouqe"
#define F29 "ladi buig"
#define F30 "la parat moshe rabeno" 

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

	virtual float getPlayerAvarageAnswerTime(std::string username) override;
	virtual int getNumOfCorrectAnswers(std::string username) override;
	virtual int getNumOfTotalAnswers(std::string username) override;
	virtual int getNumOfPlayerGames(std::string username) override;
private:										
	sqlite3* dataBase;
	void addQuestions();
	void selectBy(std::string src, std::string byWhat, std::string what, sqlite3* db);
	void insertTo(std::string toWhere, std::string headers, std::string what, sqlite3* db);

};