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

	//Setters
	void SetId(const int& id);
	void SetQuestion(const std::string& question);
	void SetRightAnswer(const int& rightAnswer);

	//Getters
	const int& GetId() const;
	const std::string& GetQuestion() const;
	const int& GetRightAnswer() const;

public:
	friend std::istream& operator>>(std::istream& is, NumericalAnswerQuestion& numericalAnswerQuestion);
	friend std::ostream& operator<<(std::ostream& os, const NumericalAnswerQuestion& numericalAnswerQuestion);
	friend bool operator==(const NumericalAnswerQuestion& naq1, const NumericalAnswerQuestion& naq2);
};