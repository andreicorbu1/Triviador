#include "NumericalAnswerQuestion.h"

NumericalAnswerQuestion::NumericalAnswerQuestion(const std::string& question, int rightAnswer) :
    Question(question, rightAnswer)
{
    // empty
}

NumericalAnswerQuestion::NumericalAnswerQuestion(const NumericalAnswerQuestion& numericalAnswerQuestion)
{
    *this = numericalAnswerQuestion;   
}

NumericalAnswerQuestion::NumericalAnswerQuestion(NumericalAnswerQuestion&& numericalAnswerQuestion) noexcept
{
    *this = std::move(numericalAnswerQuestion);
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

NumericalAnswerQuestion& NumericalAnswerQuestion::operator=(const NumericalAnswerQuestion& numericalAnswerQuestion)
{
    if (this == &numericalAnswerQuestion)
    {
        return *this;
    }
    Question::SetId(numericalAnswerQuestion.GetId());
    Question::SetQuestion(numericalAnswerQuestion.GetQuestion());
    Question::SetRightAnswer(numericalAnswerQuestion.GetRightAnswer());
    return *this;
}

NumericalAnswerQuestion& NumericalAnswerQuestion::operator=(NumericalAnswerQuestion&& numericalAnswerQuestion) noexcept
{
    if (this == &numericalAnswerQuestion)
    {
        return *this;
    }
    Question::SetId(numericalAnswerQuestion.GetId());
    Question::SetQuestion(numericalAnswerQuestion.GetQuestion());
    Question::SetRightAnswer(numericalAnswerQuestion.GetRightAnswer());
    new(&numericalAnswerQuestion)NumericalAnswerQuestion;
    return *this;
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