#pragma once
#include <iostream>
#include <string>

template <class T>
class Question
{
public:
    Question();
    Question(const std::string& question, const T& rightAnswer);
    Question(const Question& question);
    Question(Question&& question) noexcept;

    // Setters
    void SetId(const int& id);
    void SetQuestion(const std::string& question);
    void SetRightAnswer(const T& rightAnswer);

    // Getters
    const int& GetId() const;
    const std::string& GetQuestion() const;
    const T& GetRightAnswer() const;

    // Operators
    friend std::istream& operator>>(std::istream& is, Question<T>& question);
    Question& operator=(const Question& question);
    Question& operator=(Question&& question) noexcept;

private:
    int m_id;
    std::string m_question;
    T m_rightAnswer;
};

template <class T>
inline Question<T>::Question()
{
    m_id = -1;
    m_question = "";
    m_rightAnswer = T();
}

template <class T>
inline Question<T>::Question(const std::string& question, const T& rightAnswer) :
    m_question(question), m_rightAnswer(rightAnswer)
{
    m_id = -1;
}

template<class T>
inline Question<T>::Question(const Question& question)
{
    *this = question;
}

template<class T>
inline Question<T>::Question(Question&& question) noexcept
{
    *this = question;
    question.m_id=-1;
    question.m_question = nullptr;
    question.m_rightAnswer = {};
}

template <class T>
inline void Question<T>::SetId(const int& id)
{
    m_id = id;
}

template <class T>
inline void Question<T>::SetQuestion(const std::string& question)
{
    m_question = question;
}

template <class T>
inline void Question<T>::SetRightAnswer(const T& rightAnswer)
{
    m_rightAnswer = rightAnswer;
}

template <class T>
inline const int& Question<T>::GetId() const
{
    return m_id;
}

template <class T>
inline const std::string& Question<T>::GetQuestion() const
{
    return m_question;
}

template <class T>
inline const T& Question<T>::GetRightAnswer() const
{
    return m_rightAnswer;
}

template<class T>
inline Question<T>& Question<T>::operator=(const Question& question)
{
    m_id = question.m_id;
    m_question = question.m_question;
    m_rightAnswer = question.m_rightAnswer;
    return *this;
}

template<class T>
inline Question<T>& Question<T>::operator=(Question&& question) noexcept
{
    if (this == &question)
    {
        return *this;
    }
    m_id = question.m_id;
    m_question = question.m_question;
    m_rightAnswer = question.m_rightAnswer;
    new(&question)Question;
    return *this;
}

template <class T>
std::istream& operator>>(std::istream& is, const Question<T>& question)
{
    std::getline(is, question.m_question);
    is >> question.m_rightAnswer;
    return is;
}