#pragma once
#include <iostream>
#include <string>

template <class T>
class Question
{
public:
	Question();
	Question(const std::string& question, const T& rightAnswer);

    // Operators
    friend std::istream& operator>>(std::istream& is, Question<T>& question);

protected:
    int m_id;
    std::string m_question;
    T m_rightAnswer;
};

template<class T>
inline Question<T>::Question()
{
	m_id = -1;
    m_question = "";
    m_rightAnswer = T();
}

template<class T>
inline Question<T>::Question(const std::string& question, const T& rightAnswer) :
    m_question(question), m_rightAnswer(rightAnswer)
{
	m_id = -1;
}

template <class T>
std::istream& operator>>(std::istream& is, const Question<T>& question)
{
	std::getline(is, question.m_question);
	is >> question.m_rightAnswer;
	return is;
}