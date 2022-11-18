#include "NumericalAnswerQuestion.h"

template<typename T>
std::istream& operator>>(std::istream& is, NumericalAnswerQuestion<T>& numericalAnswerQuestion)
{
	std::getline(is, numericalAnswerQuestion.m_question);
	is >> numericalAnswerQuestion;
	return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const NumericalAnswerQuestion<T>& numericalAnswerQuestion)
{
	os <<"\n";
	os << "The Question is: " << numericalAnswerQuestion.m_question << "\n";
	os << "The Answer of the Question is: " << numericalAnswerQuestion.m_rightAnswer << "\n";
	return os;
}
