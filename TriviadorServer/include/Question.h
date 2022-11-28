#pragma once
#include <string>
#include <iostream>
//#include "QuestionsIntoDataBase.h"
template <class T>
class Question
{
public:
	Question() = default;
	Question(const std::string& question, const T& rightAnswer, uint16_t numberOfAnswers);
	const std::string& GetQuestion() const;
	const T& GetRightAnswer() const;
	uint16_t GetNumberOfAnswers() const;
	const std::string& GetInputFileName() const;
	void SetQuestion(const std::string& question);
	void SetRightAnswer(const T& m_rightAnswer);
	void SetNumberOfAnswers(uint16_t numberOfAnswers);
	void SetInputFileName(const std::string& fileName);
	//friend class QuestionsIntoDataBase;

protected:
	int m_id;
	std::string m_question;
	T m_rightAnswer;
	uint16_t m_numberOfAnswers;
	std::string m_inputFileName;
};

template<class T>
inline Question<T>::Question(const std::string& question, const T& rightAnswer, uint16_t numberOfAnswers) :
	m_question(question),
	m_rightAnswer(rightAnswer),
	m_numberOfAnswers(numberOfAnswers)
{
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
inline uint16_t Question<T>::GetNumberOfAnswers() const
{
	return m_numberOfAnswers;
}

template<class T>
inline const std::string& Question<T>::GetInputFileName() const
{
	return m_inputFileName;
}

template<class T>
inline void Question<T>::SetQuestion(const std::string& question)
{
	m_question = question;
}

template<class T>
inline void Question<T>::SetRightAnswer(const T& m_rightAnswer)
{
	m_rightAnswer = m_rightAnswer;
}

template<class T>
inline void Question<T>::SetNumberOfAnswers(uint16_t numberOfAnswers)
{
	m_numberOfAnswers = numberOfAnswers;
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

//
//#pragma once
//#include <string>
//#include <iostream>
//template <class T>
//class Question
//{
//public:
//	Question() = default;
//	Question(const std::string& question, const T& rightAnswer, uint16_t numberOfAnswers);
//	const std::string& GetQuestion() const;
//	const T& GetRightAnswer() const;
//	uint16_t GetNumberOfAnswers() const;
//	const std::string& GetFileName() const;
//	void SetQuestion(const std::string& question);
//	void SetRightAnswer(const T& m_rightAnswer);
//	void SetNumberOfAnswers(uint16_t numberOfAnswers);
//	void SetFileName(const std::string& fileName);
//
//protected:
//	std::string m_question;
//	T m_rightAnswer;
//	uint16_t m_numberOfAnswers;
//	std::string m_inputFileName;
//};
//
//template<class T>
//inline Question<T>::Question(const std::string& question, const T& rightAnswer, uint16_t numberOfAnswers) :
//	m_question(question),
//	m_rightAnswer(rightAnswer),
//	m_numberOfAnswers(numberOfAnswers)
//{
//}
//
//template<class T>
//inline const std::string& Question<T>::GetQuestion() const
//{
//	return m_question;
//}
//
//template<class T>
//inline const T& Question<T>::GetRightAnswer() const
//{
//	return m_rightAnswer;
//}
//
//template<class T>
//inline uint16_t Question<T>::GetNumberOfAnswers() const
//{
//	return m_numberOfAnswers;
//}
//
//template<class T>
//inline const std::string& Question<T>::GetInputFileName() const
//{
//	return m_inputFileName;
//}
//
//template<class T>
//inline void Question<T>::SetQuestion(const std::string& question)
//{
//	m_question = question;
//}
//
//template<class T>
//inline void Question<T>::SetRightAnswer(const T& m_rightAnswer)
//{
//	m_rightAnswer = m_rightAnswer;
//}
//
//template<class T>
//inline void Question<T>::SetNumberOfAnswers(uint16_t numberOfAnswers)
//{
//	m_numberOfAnswers = numberOfAnswers;
//}
//
//template<class T>
//inline void Question<T>::SetInputFileName(const std::string& fileName)
//{
//	m_inputFileName = fileName;
//}
//
//template <class T>
//std::istream& operator>>(std::istream& is, const Question<T>& question)
//{
//	std::getline(is, question.m_question);
//	is >> question.m_rightAnswer;
//	return is;
//}


