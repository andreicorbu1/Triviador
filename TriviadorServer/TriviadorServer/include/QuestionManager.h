#pragma once
#include "MultipleAnswerQuestion.h"
#include "NumericalAnswerQuestion.h"
#include <fstream>
#include <random>
#include <unordered_set>
#include <sqlite_orm/sqlite_orm.h>
#include "utils.h"
#include <crow.h>

namespace sql = sqlite_orm;

inline auto CreateStorageForQuestions(const std::string& path)
{
	return sql::make_storage(path,
		sql::make_table("MultipleAnswerQuestions",
		sql::make_column("id", &MultipleAnswerQuestion::SetId, &MultipleAnswerQuestion::GetId, sql::primary_key()),
		sql::make_column("question", &MultipleAnswerQuestion::SetQuestion, &MultipleAnswerQuestion::GetQuestion),
		sql::make_column("rightAnswer", &MultipleAnswerQuestion::SetRightAnswer, &MultipleAnswerQuestion::GetRightAnswer),
		sql::make_column("answer1", &MultipleAnswerQuestion::SetAnswer<0>, &MultipleAnswerQuestion::GetAnswer<0>),
		sql::make_column("answer2", &MultipleAnswerQuestion::SetAnswer<1>, &MultipleAnswerQuestion::GetAnswer<1>),
		sql::make_column("answer3", &MultipleAnswerQuestion::SetAnswer<2>, &MultipleAnswerQuestion::GetAnswer<2>),
		sql::make_column("answer4", &MultipleAnswerQuestion::SetAnswer<3>, &MultipleAnswerQuestion::GetAnswer<3>)
	),
		sql::make_table("NumericalAnswerQuestion",
		sql::make_column("id", &NumericalAnswerQuestion::SetId, &NumericalAnswerQuestion::GetId, sql::primary_key()),
		sql::make_column("question", &NumericalAnswerQuestion::SetQuestion, &NumericalAnswerQuestion::GetQuestion),
		sql::make_column("rightAnswer", &NumericalAnswerQuestion::SetRightAnswer, &NumericalAnswerQuestion::GetRightAnswer)
	)
	);
}

using StorageForQM = decltype(CreateStorageForQuestions(""));

class QuestionManager
{
public:
	QuestionManager() = default;
	explicit QuestionManager(const std::string& path);
	void AddQuestion(const MultipleAnswerQuestion& question);
	void AddQuestion(const NumericalAnswerQuestion& question);
	void RemoveMultipleAnswerQuestion(int id);
	void RemoveNumericalAnswerQuestion(int id);
	void UpdateQuestion(const MultipleAnswerQuestion& multipleAnswerQuestion);
	void UpdateQuestion(const NumericalAnswerQuestion& numericalAnswerQuestion);
	MultipleAnswerQuestion GetMultipleAnswerQuestion(int id);
	NumericalAnswerQuestion GetNumericalAnswerQuestion(int id);
	int GetRandomMultipleAnswerQuestionsID();
	int GetRandomNumericalAnswerQuestionsID();
	void Clear();
	void PopulateStorage();
private:
	StorageForQM m_storage;
	std::unordered_set<int>m_alreadyChoosedMultipleAnswerQuestionsID;
	std::unordered_set<int>m_alreadyChoosedNumericalAnswerQuestionsID;
};