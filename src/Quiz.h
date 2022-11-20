#pragma once
#include <iostream>
#include "NumericalAnswerQuestion.h"
#include "NumericalAnswerQuestion.cpp"
#include "MultipleAnswerQuestion.h"
#include <unordered_set>
#include <fstream>

class Quiz
{
private:
	struct HashFunctionForNumericalQuestion
	{
		size_t operator()(const NumericalAnswerQuestion<int>& numericalAnswerQuestion) const;
	};
	struct HashFunctionForMultipleAnswerQuestion
	{
		size_t operator()(const MultipleAnswerQuestion& multipleAnswerQuestion) const;
	};
public:
	Quiz();
	Quiz(const std::unordered_set<NumericalAnswerQuestion<int>, HashFunctionForNumericalQuestion>& numericalAnswerQuestions,
		const std::unordered_set<MultipleAnswerQuestion, HashFunctionForMultipleAnswerQuestion>& multipleAnswerQuestion);

public:
	void SetNumericalAnswerQuestions(const std::unordered_set<NumericalAnswerQuestion<int>, HashFunctionForNumericalQuestion>& numericalAnswerQuestions);
	void SetMultipleAnswerQuestions(const std::unordered_set<MultipleAnswerQuestion, HashFunctionForMultipleAnswerQuestion>& multipleAnswerQuestions);
	const std::unordered_set<NumericalAnswerQuestion<int>, HashFunctionForNumericalQuestion>& GetNumericalAnswerQuestions() const;
	const std::unordered_set<MultipleAnswerQuestion, HashFunctionForMultipleAnswerQuestion>& GetMultipleAnswerQuestions() const;

	void ReadFromFile(std::string fileName, bool readNumericalAnswerQuestion = true);
	void Start();
private:
	std::unordered_set<NumericalAnswerQuestion<int>, HashFunctionForNumericalQuestion>m_numericalAnswerQuestions;
	std::unordered_set<MultipleAnswerQuestion, HashFunctionForMultipleAnswerQuestion>m_multipleAnswerQuestions;
};

