#include "BasicQuestion.h"

BasicQuestion::BasicQuestion(const std::string& question, const std::string& answer):
	m_question(question), 
	m_answer(answer)
{
}

void BasicQuestion::SetQuestion(const std::string& question)
{
	m_question = question;
}

void BasicQuestion::SetAnswer(const std::string& answer)
{
	m_answer = answer;
}

const std::string& BasicQuestion::GetQuestion() const
{
	return m_question;
}

const std::string& BasicQuestion::GetAnswer() const
{
	return m_question;
}
