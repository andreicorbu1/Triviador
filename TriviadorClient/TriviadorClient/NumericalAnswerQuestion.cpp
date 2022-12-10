#include "NumericalAnswerQuestion.h"

NumericalAnswerQuestion::NumericalAnswerQuestion()
{
}

cpr::Response NumericalAnswerQuestion::GetQuestionFromServer() 
{
    return cpr::Get(cpr::Url("localhost:18080/NumericalAnswerQuestion"));
}


bool NumericalAnswerQuestion::CheckIfAnswerIsCorect(const int& answer) 
{
    //TODO
    return false;
}

void NumericalAnswerQuestion::ParseFromJson()
{
    cpr::Response response = GetQuestionFromServer();
    auto value = crow::json::load(response.text);
    Question::SetQuestion(value["question"].s());
}

std::string NumericalAnswerQuestion::GetQuestion()
{
    ParseFromJson();
    return Question::GetQuestion();
}

