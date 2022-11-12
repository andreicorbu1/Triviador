#pragma once
#include "BasicQuestion.h"
#include <iostream>
#include <vector>
#include <string>
class MultipleAnswerQuestion : public BasicQuestion
{
public:
	MultipleAnswerQuestion() = default;
	MultipleAnswerQuestion(const std::string& question, const std::string& rightAnswer,
		const std::vector<std::string>& answers);

public:
	void SetAnswers(const std::vector<std::string>& answers);
	const std::vector<std::string> GetAnswers();

public:
	friend std::istream& operator>>(std::istream& is, MultipleAnswerQuestion& multipleAnswerQuestion);
	friend std::ostream& operator<<(std::ostream& os, const MultipleAnswerQuestion& multipleAnswerQuestion);

private:
	std::vector<std::string> m_answers;
};
