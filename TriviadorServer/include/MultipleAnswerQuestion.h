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

    //Setters
    void SetId(const int& id);
    void SetQuestion(const std::string& question);
    void SetRightAnswer(const std::string& rightAnswer);
    void SetAnswer1(const std::string& answer);
    void SetAnswer2(const std::string& answer);
    void SetAnswer3(const std::string& answer);
    void SetAnswer4(const std::string& answer);

    //Getters
    const int& GetId() const;
    const std::string& GetQuestion() const;
    const std::string& GetRightAnswer() const;
    const std::string& GetAnswer1() const;
    const std::string& GetAnswer2() const;
    const std::string& GetAnswer3() const;
    const std::string& GetAnswer4() const;
    size_t GetNumberOfAnswers() const;

    // Operators
    friend std::istream& operator>>(std::istream& is, MultipleAnswerQuestion& multipleAnswerQuestion);
    friend std::ostream& operator<<(std::ostream& os, const MultipleAnswerQuestion& multipleAnswerQuestion);
    friend bool operator==(const MultipleAnswerQuestion& maq1, const MultipleAnswerQuestion& maq2);

private:
    std::vector<std::string> m_answers;
};
