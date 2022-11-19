#pragma once
#include <iostream>
#include <vector>
#include <string>
class MultipleAnswerQuestion
{
public:
	MultipleAnswerQuestion() = default;
	MultipleAnswerQuestion(const std::string& question, const std::string& rightAnswer,
		const std::vector<std::string>& answers);

public:
	void SetQuestion(const std::string& question);
	void SetRightAnswer(const std::string& rightAnswer);
	const std::string& GetQuestion() const;
	const std::string& GetRightAnswer() const;
	void SetAnswers(const std::vector<std::string>& answers);
	const std::vector<std::string>& GetAnswers() const;

public:
	friend std::istream& operator>>(std::istream& is, MultipleAnswerQuestion& multipleAnswerQuestion);
	friend std::ostream& operator<<(std::ostream& os, const MultipleAnswerQuestion& multipleAnswerQuestion);
	friend bool operator==(const MultipleAnswerQuestion& map1, const MultipleAnswerQuestion& map2);

private:
	std::string m_question;
	std::string m_rightAnswer;
	std::vector<std::string> m_answers;
};
