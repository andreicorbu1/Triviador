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
	int GetRightAnswer();
	std::string GetQuestion() const;

private:
	void ParseFromJson();
	cpr::Response GetQuestionFromServer();
};

