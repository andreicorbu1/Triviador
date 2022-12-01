#include "NumericalAnswerQuestion.h"

NumericalAnswerQuestion::NumericalAnswerQuestion(const std::string& question, int rightAnswer) :
    Question(question, rightAnswer)
{
    // empty
}

void NumericalAnswerQuestion::SetId(const int& id)
{
    Question::SetId(id);
}

void NumericalAnswerQuestion::SetQuestion(const std::string& question)
{
    Question::SetQuestion(question);
}

void NumericalAnswerQuestion::SetRightAnswer(const int& rightAnswer)
{
    Question::SetRightAnswer(rightAnswer);
}

const int& NumericalAnswerQuestion::GetId() const
{
    return Question::GetId();
}

const std::string& NumericalAnswerQuestion::GetQuestion() const
{
    return Question::GetQuestion();
}

const int& NumericalAnswerQuestion::GetRightAnswer() const
{
    return Question::GetRightAnswer();
}

std::istream& operator>>(std::istream& is, NumericalAnswerQuestion& numericalAnswerQuestion)
{
    std::string question;
    int rightAnswer;

    std::getline(is, question);
    is >> rightAnswer;
    is.ignore(1024, '\n');
    numericalAnswerQuestion = NumericalAnswerQuestion(question, rightAnswer);

    return is;
}

std::ostream& operator<<(std::ostream& os, const NumericalAnswerQuestion& numericalAnswerQuestion)
{
    os << "Intrebarea este: " << numericalAnswerQuestion.GetQuestion() << "\n";
    return os;
}

bool operator==(const NumericalAnswerQuestion& naq1, const NumericalAnswerQuestion& naq2)
{
    return naq1.GetQuestion() == naq2.GetQuestion() && naq1.GetRightAnswer() == naq2.GetRightAnswer();
}