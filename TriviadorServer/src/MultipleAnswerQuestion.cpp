#include "MultipleAnswerQuestion.h"

MultipleAnswerQuestion::MultipleAnswerQuestion(const std::string& question, const std::string& rightAnswer,
	const std::vector<std::string>& answers) :
	Question(question, rightAnswer),
	m_answers(answers)
{
	m_answers.resize(m_numberOfAnswers);
}

void MultipleAnswerQuestion::SetAnswers(const std::vector<std::string>& answers)
{
	m_answers = answers;
}

void MultipleAnswerQuestion::SetNumeberOfAnswers(uint16_t numberOfAnswers)
{
	m_numberOfAnswers = numberOfAnswers;
}

const std::vector<std::string>& MultipleAnswerQuestion::GetAnswers() const
{
	return m_answers;
}

uint16_t MultipleAnswerQuestion::GetNumberOfAnswers() const
{
	return m_numberOfAnswers;
}

std::istream& operator>>(std::istream& is, MultipleAnswerQuestion& multipleAnswerQuestion)
{
	std::getline(is, multipleAnswerQuestion.m_question);
	std::getline(is, multipleAnswerQuestion.m_rightAnswer);
	multipleAnswerQuestion.m_answers.resize(multipleAnswerQuestion.m_numberOfAnswers);
	is.ignore(1024, '\n');
	is.ignore(1024, '\n');
	return is;
}

std::ostream& operator<<(std::ostream& os, const MultipleAnswerQuestion& multipleAnswerQuestion)
{
	os << "Intrebarea este: " << multipleAnswerQuestion.m_question << "\n";
	//os << "Raspunsul corect este: " << multipleAnswerQuestion.m_rightAnswer << "\n";
	os << "Variantele de raspuns sunt:\n";
	for (size_t i = 0; i < multipleAnswerQuestion.m_numberOfAnswers; i++)
	{
		os << multipleAnswerQuestion.m_answers[i] << "\n";
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

uint16_t MultipleAnswerQuestion::m_numberOfAnswers = 4;

