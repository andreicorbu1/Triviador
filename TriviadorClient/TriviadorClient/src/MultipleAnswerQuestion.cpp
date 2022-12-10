#include "MultipleAnswerQuestion.h"

MultipleAnswerQuestion::MultipleAnswerQuestion()
{
    ParseFromJson();
}

bool MultipleAnswerQuestion::CheckIfAnswerIsCorect(const std::string& answer)
{
    return false;
}

std::string MultipleAnswerQuestion::GetQuestion() const
{
    return Question::GetQuestion();
}

std::string MultipleAnswerQuestion::GetAnswer(int index) const
{
    return m_answers[index];
}


void MultipleAnswerQuestion::ParseFromJson()
{
    cpr::Response response = GetQuestionFromServer();
    auto value = crow::json::load(response.text);
    Question::SetQuestion(value["question"].s());
    m_answers[0] = value["answer1"].s();
    m_answers[1] = value["answer2"].s();
    m_answers[2] = value["answer3"].s();
    m_answers[3] = value["answer4"].s();
}

cpr::Response MultipleAnswerQuestion::GetQuestionFromServer()
{
    return cpr::Get(cpr::Url("localhost:18080/MultipleAnswerQuestion"));
}
