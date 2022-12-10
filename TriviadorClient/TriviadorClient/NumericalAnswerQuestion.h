#pragma once
#include "Question.h"
#include <string>

class NumericalAnswerQuestion:
	public Question<int>
{
private:
	std::string m_question;
public:
	NumericalAnswerQuestion();
	void CheckIfAnswerIsCorect(int answer);
	void ParseFromJson();
	const std::string& GetQuestion();
private:
	cpr::Response GetQuestionFromServer();
};

