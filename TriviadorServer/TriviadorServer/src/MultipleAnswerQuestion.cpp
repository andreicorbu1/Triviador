﻿#include "MultipleAnswerQuestion.h"

MultipleAnswerQuestion::MultipleAnswerQuestion()
{
	m_answers = std::vector<std::string>(kNumberOfAnswers);
}

MultipleAnswerQuestion::MultipleAnswerQuestion(const std::string& question, const std::string& rightAnswer,
	const std::vector<std::string>& answers) :
	Question(question, rightAnswer), m_answers(answers)
{
	m_answers.resize(kNumberOfAnswers);
}

MultipleAnswerQuestion::MultipleAnswerQuestion(const MultipleAnswerQuestion& multipleAnswerQuestion)
{
	*this = multipleAnswerQuestion;
}

MultipleAnswerQuestion::MultipleAnswerQuestion(MultipleAnswerQuestion&& multipleAnswerQuestion) noexcept
{
	*this = std::move(multipleAnswerQuestion);
}

void MultipleAnswerQuestion::SetId(const int& id)
{
	Question::SetId(id);
}

void MultipleAnswerQuestion::SetQuestion(const std::string& question)
{
	Question::SetQuestion(question);
}

void MultipleAnswerQuestion::SetRightAnswer(const std::string& rightAnswer)
{
	Question<std::string>::SetRightAnswer(rightAnswer);
}

int MultipleAnswerQuestion::GetId() const
{
	return Question::GetId();
}

std::string MultipleAnswerQuestion::GetQuestion() const
{
	return Question::GetQuestion();
}

std::string MultipleAnswerQuestion::GetRightAnswer() const
{
	return Question<std::string>::GetRightAnswer();
}

std::vector<std::string> MultipleAnswerQuestion::GetAnswers() const
{
	return m_answers;
}

size_t MultipleAnswerQuestion::GetNumberOfAnswers() const
{
	return m_answers.size();
}

MultipleAnswerQuestion& MultipleAnswerQuestion::operator=(const MultipleAnswerQuestion& multipleAnswerQuestion)
{
	if (this != &multipleAnswerQuestion)
	{
		Question::SetId(multipleAnswerQuestion.GetId());
		Question::SetQuestion(multipleAnswerQuestion.GetQuestion());
		Question::SetRightAnswer(multipleAnswerQuestion.GetRightAnswer());
		m_answers = multipleAnswerQuestion.m_answers;
	}
	return *this;
}

MultipleAnswerQuestion& MultipleAnswerQuestion::operator=(MultipleAnswerQuestion&& multipleAnswerQuestion) noexcept
{
	if (this != &multipleAnswerQuestion)
	{
		Question::SetId(multipleAnswerQuestion.GetId());
		Question::SetQuestion(multipleAnswerQuestion.GetQuestion());
		Question::SetRightAnswer(multipleAnswerQuestion.GetRightAnswer());
		m_answers = std::move(multipleAnswerQuestion.m_answers);
		new(&multipleAnswerQuestion)MultipleAnswerQuestion;
	}
	return *this;
}

std::istream& operator>>(std::istream& is, MultipleAnswerQuestion& multipleAnswerQuestion)
{
	std::string question;
	std::string rightAnswer;
	std::vector<std::string> answers(MultipleAnswerQuestion::kNumberOfAnswers);

	std::getline(is, question);
	std::getline(is, rightAnswer);

	for (size_t i = 0; i < answers.size(); i++)
	{
		std::getline(is, answers[i]);
	}

	multipleAnswerQuestion.SetQuestion(question);
	multipleAnswerQuestion.SetRightAnswer(rightAnswer);
	multipleAnswerQuestion.m_answers = answers;

	return is;
}

std::ostream& operator<<(std::ostream& os, const MultipleAnswerQuestion& multipleAnswerQuestion)
{
	os << "Intrebarea este: " << multipleAnswerQuestion.GetQuestion() << "\n";
	os << "Variantele de raspuns sunt:\n";
	for (size_t i = 0; i < multipleAnswerQuestion.GetNumberOfAnswers(); i++)
	{
		os << multipleAnswerQuestion.m_answers[i] << "\n";
	}
	return os;
}

bool operator==(const MultipleAnswerQuestion& maq1, const MultipleAnswerQuestion& maq2)
{
	return maq1.GetQuestion() == maq2.GetQuestion() &&
		maq1.GetRightAnswer() == maq2.GetRightAnswer() &&
		maq1.m_answers == maq2.m_answers;
}
