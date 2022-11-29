#pragma once
#include "NumericalAnswerQuestion.h"
#include "MultipleAnswerQuestion.h"
//#include "Question.h"
#include <sqlite_orm/sqlite_orm.h>

namespace sql = sqlite_orm;

struct QuestionStruct
{
	int m_id;
	std::string m_question;
	std::string m_rightAnswer;
	std::string m_answer1;
	std::string m_answer2;
	std::string m_answer3;
	std::string m_answer4;
};

//inline auto CreateStorageForQuestions(const std::string& databaseFileName)
//{
//	auto db = sql::make_storage(
//		databaseFileName,
//		sql::make_table
//		(
//			"MultipleAnswerQuestions",
//			sql::make_column("id", &MultipleAnswerQuestion::GetID, &MultipleAnswerQuestion::SetID, sql::autoincrement(), sql::primary_key())/*,
//			sql::make_column("question", &MultipleAnswerQuestion::GetQuestion, &MultipleAnswerQuestion::SetQuestion),
//			sql::make_column("right_answer", &MultipleAnswerQuestion::GetRightAnswer, &MultipleAnswerQuestion::SetRightAnswer)*/
//			/*sql::make_column("answer_1", &QuestionStruct::m_answer1),
//			sql::make_column("answer_2", &QuestionStruct::m_answer2),
//			sql::make_column("answer_3", &QuestionStruct::m_answer3),
//			sql::make_column("answer_4", &QuestionStruct::m_answer4)*/
//		)/*,
//		sql::make_table
//		(
//			"Numerical Answer Questions",
//			sql::make_column("id", &QuestionStruct<int>::m_id, sql::autoincrement(), sql::primary_key()),
//			sql::make_column("Question", &QuestionStruct<int>::m_question),
//			sql::make_column("Right Answer", &QuestionStruct<int>::m_rightAnswer)
//		)*/
//	);
//	db.sync_schema();
//	return db;
//}

//using StorageForQM = decltype(CreateStorageForQuestions(""));

class QuestionsManager
{
public:
	QuestionsManager()=default;
	//void AddQuestion(MultipleAnswerQuestion s);
private:
	//StorageForQM db = CreateStorageForQuestions("resource/Questions1.sqlite");
};


