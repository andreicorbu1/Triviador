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
	NumericalAnswerQuestion(const NumericalAnswerQuestion& numericalAnswerQuestion);
	NumericalAnswerQuestion(NumericalAnswerQuestion&& numericalAnswerQuestion) noexcept;

	//Setters
	void SetId(const int& id);
	void SetQuestion(const std::string& question);
	void SetRightAnswer(const int& rightAnswer);

	//Getters
	int GetId() const;
	std::string GetQuestion() const;
	int GetRightAnswer() const;

public:
	friend std::istream& operator>>(std::istream& is, NumericalAnswerQuestion& numericalAnswerQuestion);
	friend std::ostream& operator<<(std::ostream& os, const NumericalAnswerQuestion& numericalAnswerQuestion);
	friend bool operator==(const NumericalAnswerQuestion& naq1, const NumericalAnswerQuestion& naq2);
	NumericalAnswerQuestion& operator=(const NumericalAnswerQuestion& numericalAnswerQuestion);
	NumericalAnswerQuestion& operator=(NumericalAnswerQuestion&& numericalAnswerQuestion) noexcept;
};