#pragma once
#include <cpr/cpr.h>
#include <crow.h>

template <class T>
class Question
{
private:
	std::string m_question;
public:
	//Getters
	const std::string& GetQuestion() const;
	virtual cpr::Response GetQuestionFromServer() = 0;

	//Setters
	void SetQuestion(const std::string& question);

	virtual bool CheckIfAnswerIsCorect(const T& answer) = 0;
};

template<class T>
inline const std::string& Question<T>::GetQuestion() const
{
	return m_question;
}

template<class T>
inline void Question<T>::SetQuestion(const std::string& question)
{
	m_question=question;
}
