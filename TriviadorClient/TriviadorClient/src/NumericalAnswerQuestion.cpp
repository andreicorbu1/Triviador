#include "NumericalAnswerQuestion.h"

NumericalAnswerQuestion::NumericalAnswerQuestion()
{
    ParseFromJson();
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
    Question::SetRightAnswer(value["right_answer"].i());
}

int NumericalAnswerQuestion::GetRightAnswer()
{
    return 0;
}

std::string NumericalAnswerQuestion::GetQuestion() const
{
    return Question::GetQuestion();
}

cpr::Response NumericalAnswerQuestion::GetQuestionFromServer()
{
    return cpr::Get(cpr::Url("localhost:18080/NumericalAnswerQuestion"));
}