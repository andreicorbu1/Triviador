#include "MultipleAnswerQuestion.h"

MultipleAnswerQuestion::MultipleAnswerQuestion(const std::string& question, const std::string& rightAnswer, uint16_t numberOfAnswers,
	const std::vector<std::string>& answers) :
	Question(question, rightAnswer, numberOfAnswers),
	m_answers(answers)
{
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
	is >> multipleAnswerQuestion.m_numberOfAnswers;
	multipleAnswerQuestion.m_answers.resize(multipleAnswerQuestion.m_numberOfAnswers);
	is.ignore(1024, '\n');
	for (size_t i = 0; i < multipleAnswerQuestion.m_numberOfAnswers; i++)
	{
		std::getline(is, multipleAnswerQuestion.m_answers[i]);
	}
	//is.ignore(1024, '\n');
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

