#pragma once
#include "MultipleAnswerQuestion.h"
#include <sqlite_orm/sqlite_orm.h>

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

private:
    StorageForQM m_storage;
};