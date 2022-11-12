#pragma once
#include <iostream>
#include <string>
class BasicQuestion
{
public:
	BasicQuestion() = default;
	BasicQuestion(const std::string& question, const std::string& rightAnswer);

public:
	void SetQuestion(const std::string& question);
	void SetRightAnswer(const std::string& rightAnswer);
	const std::string& GetQuestion() const;
	const std::string& GetRightAnswer() const;

public:
	friend std::istream& operator>>(std::istream& is, BasicQuestion& basicQuestion);
	friend std::ostream& operator<<(std::ostream& os, const BasicQuestion& basic_question);

private:
	std::string m_question;
	std::string m_rightAnswer;
};

