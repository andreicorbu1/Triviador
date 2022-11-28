#pragma once
//#include "NumericalAnswerQuestion.h"
#include "MultipleAnswerQuestion.h"
//#include "Question.h"
#include <sqlite_orm/sqlite_orm.h>
#include <string>
namespace sql = sqlite_orm;

template <typename T>
struct QuestionStruct
{
	int m_id;
	std::string m_question;
	T m_rightAnswer;
	std::string m_answer1;
	std::string m_answer2;
	std::string m_answer3;
	std::string m_answer4;
};

inline auto CreateStorageForQuestions(const std::string& databaseFileName)
{
	auto db = sql::make_storage(
		databaseFileName,
		sql::make_table
		(
			"MultipleAnswerQuestions",
			sql::make_column("id", &MultipleAnswerQuestion::SetID, &MultipleAnswerQuestion::GetID,  sql::autoincrement(), sql::primary_key()),
			sql::make_column("question", &MultipleAnswerQuestion::SetQuestion, &MultipleAnswerQuestion::GetQuestion)
			/*sql::make_column("right_answer", &QuestionStruct<std::string>::m_rightAnswer),
			sql::make_column("answer_1", &QuestionStruct<std::string>::m_answer1),
			sql::make_column("answer_2", &QuestionStruct<std::string>::m_answer2),
			sql::make_column("answer_3", &QuestionStruct<std::string>::m_answer3),
			sql::make_column("answer_4", &QuestionStruct<std::string>::m_answer4)*/
		)/*,
		sql::make_table
		(
			"Numerical Answer Questions",
			sql::make_column("id", &QuestionStruct<int>::m_id, sql::autoincrement(), sql::primary_key()),
			sql::make_column("Question", &QuestionStruct<int>::m_question),
			sql::make_column("Right Answer", &QuestionStruct<int>::m_rightAnswer)
		)*/
	);
	db.sync_schema();
	return db;
}

using StorageForQM = decltype(CreateStorageForQuestions(""));

class QuestionManager
{
public:
	QuestionManager();
	void AddQuestion(Question<std::string> s);
private:
	StorageForQM db = CreateStorageForQuestions("resource/Questions4.sqlite");
};

