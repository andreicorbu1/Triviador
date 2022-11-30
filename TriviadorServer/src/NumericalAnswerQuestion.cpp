#include "NumericalAnswerQuestion.h"

NumericalAnswerQuestion::NumericalAnswerQuestion(const std::string& question, int rightAnswer) :
	Question(question, rightAnswer)
{
    // empty
}

std::istream& operator>>(std::istream& is, NumericalAnswerQuestion& numericalAnswerQuestion)
{
    std::string question;
    int rightAnswer;

    std::getline(is, question);
    is >> rightAnswer;

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
