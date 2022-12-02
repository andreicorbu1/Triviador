#pragma once
#include "Question.h"

#include <iostream>
#include <vector>
#include <string>

class MultipleAnswerQuestion :
    public Question<std::string>
{
public:
    MultipleAnswerQuestion();
    MultipleAnswerQuestion(const std::string& question, const std::string& rightAnswer,
        const std::vector<std::string>& answers);
    MultipleAnswerQuestion(const MultipleAnswerQuestion& multipleAnswerQuestion);
    MultipleAnswerQuestion(MultipleAnswerQuestion&& multipleAnswerQuestion) noexcept;

    //Setters
    void SetId(const int& id);
    void SetQuestion(const std::string& question);
    void SetRightAnswer(const std::string& rightAnswer);
    template <size_t index>
    void SetAnswer(const std::string& answer);

    //Getters
    const int& GetId() const;
    const std::string& GetQuestion() const;
    const std::string& GetRightAnswer() const;
    template <size_t index>
    const std::string& GetAnswer() const;
    const std::vector<std::string>& GetAnswers() const;
    size_t GetNumberOfAnswers() const;

    // Operators
    friend std::istream& operator>>(std::istream& is, MultipleAnswerQuestion& multipleAnswerQuestion);
    friend std::ostream& operator<<(std::ostream& os, const MultipleAnswerQuestion& multipleAnswerQuestion);
    friend bool operator==(const MultipleAnswerQuestion& maq1, const MultipleAnswerQuestion& maq2);
    MultipleAnswerQuestion& operator=(const MultipleAnswerQuestion& multipleAnswerQuestion);
    MultipleAnswerQuestion& operator=(MultipleAnswerQuestion&& multipleAnswerQuestion) noexcept;

private:
    // Constants
    static const size_t kNumberOfAnswers = 4;

    std::vector<std::string> m_answers;
};

template<size_t index>
inline void MultipleAnswerQuestion::SetAnswer(const std::string& answer)
{
    m_answers[index] = answer;
}

template<size_t index>
inline const std::string& MultipleAnswerQuestion::GetAnswer() const
{
    return m_answers[index];
}