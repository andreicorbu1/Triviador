#include "Quiz.h"

Quiz::Quiz(std::unordered_set<NumericalAnswerQuestion<int>> numericalAnswerQuestions,
	std::unordered_set<MultipleAnswerQuestion> multipleAnswerQuestion):
m_numericalAnswerQuestions(numericalAnswerQuestions),
m_multipleAnswerQuestions(multipleAnswerQuestion)
{
}

void Quiz::SetNumericalAnswerQuestions(const std::unordered_set<NumericalAnswerQuestion<int>>& numericalAnswerQuestions)
{
	m_numericalAnswerQuestions = numericalAnswerQuestions;
}

void Quiz::SetMultipleAnswerQuestions(const std::unordered_set<MultipleAnswerQuestion>& multipleAnswerQuestions)
{
	m_multipleAnswerQuestions = multipleAnswerQuestions;
}

const std::unordered_set<NumericalAnswerQuestion<int>>& Quiz::GetNumericalAnswerQuestions() const
{
	return m_numericalAnswerQuestions;
}

const std::unordered_set<MultipleAnswerQuestion>& Quiz::GetMultipleAnswerQuestions() const
{
	return m_multipleAnswerQuestions;
}
