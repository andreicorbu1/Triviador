#pragma once
#include <string>
class BasicQuestion
{
public:
	BasicQuestion() = default;
	BasicQuestion(const std::string& question, const std::string& answer);

public:
	void SetQuestion(const std::string& question);
	void SetAnswer(const std::string& answer);
	const std::string& GetQuestion() const;
	const std::string& GetAnswer() const;

private:
	std::string m_question;
	std::string m_answer;
};

