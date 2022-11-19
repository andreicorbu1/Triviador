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
	friend std::istream& operator>>(std::istream& is, NumericalAnswerQuestion& numericalAnswerQuestion)
	{
		std::getline(is, numericalAnswerQuestion.m_question);
		is >> numericalAnswerQuestion.m_rightAnswer;

		is.ignore(1024, '\n');
		return is;
	}
	friend std::ostream& operator<<(std::ostream& os, const NumericalAnswerQuestion& numericalAnswerQuestion)
	{
		os << "\n";
		os << "The Question is: " << numericalAnswerQuestion.m_question << "\n";
		//os << "The Answer of the Question is: " << numericalAnswerQuestion.m_rightAnswer << "\n";
		return os;
	}
	friend bool operator==(const NumericalAnswerQuestion<T>& naq1, const NumericalAnswerQuestion<T>& naq2)
	{
		return naq1.m_rightAnswer == naq2.m_rightAnswer && naq1.m_question == naq2.m_question;
	}

private:
	std::string m_question;
	T m_rightAnswer;
};

template <class T>
NumericalAnswerQuestion<T>::NumericalAnswerQuestion(const std::string& question, const T& rightAnswer) :
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





