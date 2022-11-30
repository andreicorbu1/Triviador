#pragma once
#include "Question.h"
#include <iostream>
#include <string>

class NumericalAnswerQuestion :
	public Question<int>
{
public:
	NumericalAnswerQuestion() = default;
	NumericalAnswerQuestion(const std::string& question, int rightAnswer);

public:
	friend std::istream& operator>>(std::istream& is, NumericalAnswerQuestion& numericalAnswerQuestion);
	friend std::ostream& operator<<(std::ostream& os, const NumericalAnswerQuestion& numericalAnswerQuestion);
	friend bool operator==(const NumericalAnswerQuestion& naq1, const NumericalAnswerQuestion& naq2);
};





