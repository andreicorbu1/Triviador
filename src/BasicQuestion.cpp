#include "BasicQuestion.h"

BasicQuestion::BasicQuestion(const std::string& question, const std::string& rightAnswer) :
	m_question(question),
	m_rightAnswer(rightAnswer)
{
}

void BasicQuestion::SetQuestion(const std::string& question)
{
	m_question = question;
}

void BasicQuestion::SetRightAnswer(const std::string& rightAnswer)
{
	m_rightAnswer = rightAnswer;
}

const std::string& BasicQuestion::GetQuestion() const
{
	return m_question;
}

const std::string& BasicQuestion::GetRightAnswer() const
{
	return m_rightAnswer;
}

std::istream& operator>>(std::istream& is, BasicQuestion& basicQuestion)
{
	std::getline(is, basicQuestion.m_question);
	std::getline(is, basicQuestion.m_rightAnswer);
	return is;
}

std::ostream& operator<<(std::ostream& os, const BasicQuestion& basic_question)
{
	os << "\n";
	os << "The Question is: " << basic_question.m_question << "\n";
	os << "The Answer of the Question is: " << basic_question.m_rightAnswer << "\n";
	return os;
}
