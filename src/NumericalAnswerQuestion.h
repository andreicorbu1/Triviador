#pragma once
#include <iostream>
#include <string>

template<class T>
class NumericalAnswerQuestion
{
public:
	NumericalAnswerQuestion() = default;
	NumericalAnswerQuestion(const std::string& question, const T& rightAnswer);

public:
	void SetQuestion(const std::string& question);
	void SetRightAnswer(const T& rightAnswer);
	const std::string& GetQuestion() const;
	const T& GetRightAnswer() const;

public:
	friend std::istream& operator>>(std::istream& is, NumericalAnswerQuestion& numericalAnswerQuestion);
	friend std::ostream& operator<<(std::ostream& os, const NumericalAnswerQuestion& numericalAnswerQuestion);

private:
	std::string m_question;
	T m_rightAnswer;
};

template <class T>
NumericalAnswerQuestion<T>::NumericalAnswerQuestion(const std::string& question, const T& rightAnswer):
	m_question(question),
	m_rightAnswer(rightAnswer)
{
}

template <class T>
const std::string& NumericalAnswerQuestion<T>::GetQuestion() const
{
	return m_question;
}

template <class T>
const T& NumericalAnswerQuestion<T>::GetRightAnswer() const
{
	return m_rightAnswer;
}

template <class T>
void NumericalAnswerQuestion<T>::SetQuestion(const std::string& question)
{
	m_question = question;
}

template <class T>
void NumericalAnswerQuestion<T>::SetRightAnswer(const T& rightAnswer)
{
	m_rightAnswer = rightAnswer;
}

