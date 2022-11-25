#include "NumericalAnswerQuestion.h"

NumericalAnswerQuestion::NumericalAnswerQuestion(const std::string& question, int rightAnswer):
	Question(question, rightAnswer)
{
}

std::istream& operator>>(std::istream& is, NumericalAnswerQuestion& numericalAnswerQuestion)
{
	std::getline(is, numericalAnswerQuestion.m_question);
	is >> numericalAnswerQuestion.m_rightAnswer;
	return is;
}

std::ostream& operator<<(std::ostream& os, const NumericalAnswerQuestion& numericalAnswerQuestion)
{
	os << "Intrebarea este: " << numericalAnswerQuestion.m_question << "\n";
	//os << "Raspunsul corect este: " << numericalAnswerQuestion.m_rightAnswer << "\n";
	return os;
}
