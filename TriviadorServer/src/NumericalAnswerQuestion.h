#pragma once
#include "Question.h"
#include <iostream>
#include <string>

class NumericalAnswerQuestion :
	public Question<int>
{
	friend struct QuestionsIntoDataBase;

public:
	NumericalAnswerQuestion() = default;
	NumericalAnswerQuestion(const std::string& question, int rightAnswer);

public:
	friend std::istream& operator>>(std::istream& is, NumericalAnswerQuestion& numericalAnswerQuestion);
	friend std::ostream& operator<<(std::ostream& os, const NumericalAnswerQuestion& numericalAnswerQuestion);
	friend bool operator==(const NumericalAnswerQuestion& naq1, const NumericalAnswerQuestion& naq2)
	{
		return naq1.m_rightAnswer == naq2.m_rightAnswer && naq1.m_question == naq2.m_question;
	}

};





