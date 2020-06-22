#pragma once
#include "LoggedUser.h"
#include <iostream>
#include <io.h>
#include <vector>
#include <exception>
#include <list>

struct Questions
{
	std::string data;
	std::string answer;

}typedef Questions;

class IDataBase 
{
public:

	IDataBase() = default;
	virtual bool doseUserExist(std::string name) = 0;
	virtual bool doesPasswordMatch(std::string name, std::string password) = 0;
	virtual void addNewUser(std::string name, std::string password, std::string email) = 0;
	virtual std::list<Questions> getQuestions(int Id) = 0;


	//statistics
	virtual float getPlayerAvarageAnswerTime(std::string) = 0;
	virtual int getNumOfCorrectAnswers(std::string) = 0;
	virtual int getNumOfTotalAnswers(std::string) = 0;
	virtual int getNumOfPlayerGames(std::string) = 0;

	//operations on database
	virtual bool open()  = 0;
	virtual void close() = 0;
	virtual void clear() = 0;


};