#include "NumericalAnswerQuestion.h"

NumericalAnswerQuestion::NumericalAnswerQuestion()
{
}

cpr::Response NumericalAnswerQuestion::GetQuestionFromServer() 
{
    return cpr::Get(cpr::Url("localhost:18080/NumericalAnswerQuestion"));
}


void NumericalAnswerQuestion::CheckIfAnswerIsCorect(int answer) 
{
    //TODO
}

void NumericalAnswerQuestion::ParseFromJson()
{
    cpr::Response response = GetQuestionFromServer();
    auto value = crow::json::load(response.text);
    m_question = value["question"].s();
}

const std::string& NumericalAnswerQuestion::GetQuestion()
{
    if (m_question.size() == 0)
    {
        ParseFromJson();
    }
    return m_question;
}

