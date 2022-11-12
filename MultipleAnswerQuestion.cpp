#include "MultipleAnswerQuestion.h"

MultipleAnswerQuestion::MultipleAnswerQuestion(const std::string& question, const std::string& rightAnswer,
	const std::vector<std::string>& answers):
BasicQuestion(question, rightAnswer), m_answers(answers)
{
}

void MultipleAnswerQuestion::SetAnswers(const std::vector<std::string>& answers)
{
	m_answers = answers;
}

const std::vector<std::string> MultipleAnswerQuestion::GetAnswers()
{
	return m_answers;
}

std::istream& operator>>(std::istream& is, MultipleAnswerQuestion& multipleAnswerQuestion)
{
	is >> static_cast<BasicQuestion&>(multipleAnswerQuestion);
	for(size_t i=0; i<4; i++)
	{
		std::string tempAnswer;
		std::getline(is, tempAnswer);
		multipleAnswerQuestion.m_answers.push_back(tempAnswer);
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const MultipleAnswerQuestion& multipleAnswerQuestion)
{
	os << static_cast<const BasicQuestion&>(multipleAnswerQuestion);
	os << "Potential Right Answers: \n";
	for (size_t i=0; i<4; i++)
	{
		os << multipleAnswerQuestion.m_answers[i]<<"\n";
	}
	return os;
}
