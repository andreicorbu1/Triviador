#pragma once
#include <cpr/cpr.h>
#include <crow.h>

template <class T>
class Question
{
private:
	std::string m_question;
	T m_rightAnswer;
public:
	//Setters
	void SetQuestion(const std::string& question);
	void SetRightAnswer(const T& answer);

	//Getters
	const std::string& GetQuestion() const;
	const T& GetRightAnswer() const;
	virtual cpr::Response GetQuestionFromServer() = 0;

	virtual bool CheckIfAnswerIsCorect(const T& answer) = 0;
};

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
inline void Question<T>::SetQuestion(const std::string& question)
{
	m_question=question;
}

template<class T>
inline void Question<T>::SetRightAnswer(const T& rightAnswer)
{
	m_rightAnswer = rightAnswer;
}
