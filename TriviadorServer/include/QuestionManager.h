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
            sql::make_column("answer1", &MultipleAnswerQuestion::SetAnswer1, &MultipleAnswerQuestion::GetAnswer1),
            sql::make_column("answer2", &MultipleAnswerQuestion::SetAnswer2, &MultipleAnswerQuestion::GetAnswer2),
            sql::make_column("answer3", &MultipleAnswerQuestion::SetAnswer3, &MultipleAnswerQuestion::GetAnswer3),
            sql::make_column("answer4", &MultipleAnswerQuestion::SetAnswer4, &MultipleAnswerQuestion::GetAnswer4)
        )
    );
}

using StorageForQM = decltype(CreateStorageForQuestions(""));

class QuestionManager
{
public:
    QuestionManager() = default;
    explicit QuestionManager(const std::string& path);
    void AddQuestion(MultipleAnswerQuestion& s);

private:
    StorageForQM m_storage;
};