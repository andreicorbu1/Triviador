#pragma once
#include "Question.h"
#include <iostream>
#include <vector>
#include <string>

class MultipleAnswerQuestion :
	public Question<std::string>
{
public:
	MultipleAnswerQuestion() = default;
	MultipleAnswerQuestion(const std::string& question, const std::string& rightAnswer, uint16_t numberOfAnswers,
		const std::vector<std::string>& answers);

public:
	void SetAnswers(const std::vector<std::string>& answers);
	const std::vector<std::string>& GetAnswers() const;

public:
	friend std::istream& operator>>(std::istream& is, MultipleAnswerQuestion& multipleAnswerQuestion);
	friend std::ostream& operator<<(std::ostream& os, const MultipleAnswerQuestion& multipleAnswerQuestion);
	friend bool operator==(const MultipleAnswerQuestion& map1, const MultipleAnswerQuestion& map2);

private:
	std::vector<std::string> m_answers;
};
