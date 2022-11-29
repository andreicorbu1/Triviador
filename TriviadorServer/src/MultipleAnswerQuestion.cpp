#include "MultipleAnswerQuestion.h"

MultipleAnswerQuestion::MultipleAnswerQuestion() {
    m_answers = std::vector<std::string>(4);
}

MultipleAnswerQuestion::MultipleAnswerQuestion(const std::string& question, const std::string& rightAnswer,
    const std::vector<std::string>& answers) :
    Question(question, rightAnswer), m_answers(answers)
{
    m_answers.resize(4);
}

void MultipleAnswerQuestion::SetId(const int& id)
{
    m_id = id;
}

void MultipleAnswerQuestion::SetQuestion(const std::string& question)
{
    m_question = question;
}

void MultipleAnswerQuestion::SetRightAnswer(const std::string& rightAnswer)
{
    m_rightAnswer = rightAnswer;
}

void MultipleAnswerQuestion::SetAnswer1(const std::string& answer)
{
    m_answers[0] = answer;
}

void MultipleAnswerQuestion::SetAnswer2(const std::string& answer)
{
    m_answers[1] = answer;
}

void MultipleAnswerQuestion::SetAnswer3(const std::string& answer)
{
    m_answers[2] = answer;
}

void MultipleAnswerQuestion::SetAnswer4(const std::string& answer)
{
    m_answers[3] = answer;
}

const int& MultipleAnswerQuestion::GetId() const
{
    return m_id;
}

const std::string& MultipleAnswerQuestion::GetQuestion() const
{
    return m_question;
}

const std::string& MultipleAnswerQuestion::GetRightAnswer() const
{
    return m_rightAnswer;
}

const std::string& MultipleAnswerQuestion::GetAnswer1() const
{
    return m_answers[0];
}

const std::string& MultipleAnswerQuestion::GetAnswer2() const
{
    return m_answers[1];
}

const std::string& MultipleAnswerQuestion::GetAnswer3() const
{
    return m_answers[2];
}

const std::string& MultipleAnswerQuestion::GetAnswer4() const
{
    return m_answers[3];
}

size_t MultipleAnswerQuestion::GetNumberOfAnswers() const
{
    return m_answers.size();
}

std::istream& operator>>(std::istream& is, MultipleAnswerQuestion& multipleAnswerQuestion)
{
	std::getline(is, multipleAnswerQuestion.m_question);
	std::getline(is, multipleAnswerQuestion.m_rightAnswer);
	multipleAnswerQuestion.m_answers.resize(multipleAnswerQuestion.GetNumberOfAnswers());
	is.ignore(1024, '\n');
	is.ignore(1024, '\n');
	return is;
}

std::ostream& operator<<(std::ostream& os, const MultipleAnswerQuestion& multipleAnswerQuestion)
{
	os << "Intrebarea este: " << multipleAnswerQuestion.m_question << "\n";
	os << "Variantele de raspuns sunt:\n";
	for (size_t i = 0; i < multipleAnswerQuestion.GetNumberOfAnswers(); i++)
	{
		os << multipleAnswerQuestion.m_answers[i] << "\n";
	}
	return os;
}

bool operator==(const MultipleAnswerQuestion& maq1, const MultipleAnswerQuestion& maq2)
{
	if (maq1.m_rightAnswer == maq2.m_rightAnswer && maq1.m_question == maq2.m_question &&
		maq1.m_answers == maq2.m_answers)
	{
		return true;
	}
	return false;
}

