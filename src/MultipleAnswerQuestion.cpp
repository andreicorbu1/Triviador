#include "MultipleAnswerQuestion.h"

MultipleAnswerQuestion::MultipleAnswerQuestion(const std::string& question, const std::string& rightAnswer,
	const std::vector<std::string>& answers) :
	m_question(question),
	m_rightAnswer(rightAnswer),
	m_answers(answers)
{
}

void MultipleAnswerQuestion::SetQuestion(const std::string& question)
{
	m_question = question;
}

void MultipleAnswerQuestion::SetRightAnswer(const std::string& rightAnswer)
{
	m_rightAnswer = rightAnswer;
}

const std::string& MultipleAnswerQuestion::GetQuestion() const
{
	return m_question;
}

const std::string& MultipleAnswerQuestion::GetRightAnswer() const
{
	return m_rightAnswer;
}

void MultipleAnswerQuestion::SetAnswers(const std::vector<std::string>& answers)
{
	m_answers = answers;
}

const std::vector<std::string>& MultipleAnswerQuestion::GetAnswers() const
{
	return m_answers;
}

std::istream& operator>>(std::istream& is, MultipleAnswerQuestion& multipleAnswerQuestion)
{
	std::getline(is, multipleAnswerQuestion.m_question);
	std::getline(is, multipleAnswerQuestion.m_rightAnswer);
	for (size_t i = 0; i < 4; i++)
	{
		std::string tempAnswer;
		std::getline(is, tempAnswer);
		multipleAnswerQuestion.m_answers.push_back(tempAnswer);
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const MultipleAnswerQuestion& multipleAnswerQuestion)
{
	os << "\n";
	os << "The Question is: " << multipleAnswerQuestion.m_question << "\n";
	//os << "The Answer of the Question is: " << multipleAnswerQuestion.m_rightAnswer << "\n";
	os << "Potential Right Answers: \n";
	for (size_t i = 0; i < 4; i++)
	{
		os <<i+1<<". "<< multipleAnswerQuestion.m_answers[i] << "\n";
	}
	return os;
}

bool operator==(const MultipleAnswerQuestion& map1, const MultipleAnswerQuestion& map2)
{
	if (map1.m_rightAnswer == map2.m_rightAnswer && map1.m_question == map2.m_question &&
		map1.m_answers == map2.m_answers)
	{
		return true;
	}
	return false;
}
