#pragma once
#include <iostream>
#include "NumericalAnswerQuestion.h"
#include "MultipleAnswerQuestion.h"
#include <unordered_set>
class Quiz
{
public:
	Quiz() = default;
	Quiz(const std::unordered_set<NumericalAnswerQuestion<int>>& numericalAnswerQuestions,
		const std::unordered_set<MultipleAnswerQuestion>& multipleAnswerQuestion);

public:
	void SetNumericalAnswerQuestions(const std::unordered_set<NumericalAnswerQuestion<int>>& numericalAnswerQuestions);
	void SetMultipleAnswerQuestions(const std::unordered_set<MultipleAnswerQuestion>&multipleAnswerQuestions);
	const std::unordered_set<NumericalAnswerQuestion<int>>& GetNumericalAnswerQuestions() const;
	const std::unordered_set<MultipleAnswerQuestion>& GetMultipleAnswerQuestions() const;

private:
	std::unordered_set<NumericalAnswerQuestion<int>>m_numericalAnswerQuestions;
	std::unordered_set<MultipleAnswerQuestion>m_multipleAnswerQuestions;
};

