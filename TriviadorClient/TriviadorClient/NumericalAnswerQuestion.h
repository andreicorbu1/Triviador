#pragma once
#include "Question.h"
#include <string>

class NumericalAnswerQuestion:
	public Question<int>
{
public:
	NumericalAnswerQuestion();

	bool CheckIfAnswerIsCorect(const int& answer);
	
	//Getters
	std::string GetQuestion();

private:
	void ParseFromJson();
	cpr::Response GetQuestionFromServer();
};

