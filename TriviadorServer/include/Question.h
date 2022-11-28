#pragma once
#include <string>
#include <iostream>

template <class T>
class Question
{
public:
	Question() = default;
	Question(const std::string& question, const T& rightAnswer);

	//Setters
	void SetID(int id);
	void SetQuestion(const std::string& question);
	void SetRightAnswer(const T& rightAnswer);
	void SetInputFileName(const std::string& fileName);

	//Getters
	const int& GetID() const;
	const std::string& GetQuestion() const;
	const T& GetRightAnswer() const;
	const std::string& GetInputFileName() const;

protected:
	int m_id;
	std::string m_question;
	T m_rightAnswer;
	std::string m_inputFileName;
};

template<class T>
inline const int& Question<T>::GetID() const
{
	return m_id;
}

template<class T>
inline const std::string& Question<T>::GetQuestion() const
{
	return m_question;
}

template<class T>
inline const T& Question<T>::GetRightAnswer() const
{
	return m_rightAnswer;
}

template<class T>
inline const std::string& Question<T>::GetInputFileName() const
{
	return m_inputFileName;
}

template<class T>
inline Question<T>::Question(const std::string& question, const T& rightAnswer):
	m_question(question),
	m_rightAnswer(rightAnswer)
{
}

template<class T>
inline void Question<T>::SetID(int id)
{
	m_id = id;
}

template<class T>
inline void Question<T>::SetQuestion(const std::string& question)
{
	m_question = question;
}

template<class T>
inline void Question<T>::SetRightAnswer(const T& rightAnswer)
{
	m_rightAnswer = rightAnswer;
}


template<class T>
inline void Question<T>::SetInputFileName(const std::string& fileName)
{
	m_inputFileName = fileName;
}

template <class T>
std::istream& operator>>(std::istream& is, const Question<T>& question)
{
	std::getline(is, question.m_question);
	is >> question.m_rightAnswer;
	return is;
}

