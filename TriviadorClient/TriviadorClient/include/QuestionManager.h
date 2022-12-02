#pragma once
#include <unordered_map>

#include <Question.h>

class QuestionManager
{
public:
    QuestionManager();
    ~QuestionManager();

    void SetParentWidget(QWidget* parent = nullptr);
    void ShowMultipleAnswerQuestion();
    void ShowNumericalAnswerQuestion();
    

    void FetchQuestion();
    
private:
    QWidget* m_parent;
    const std::unordered_map<std::string, int> m_advantages = {
        {"hammer", 1},
        {"telescope", 1},
        {"parrot", 1}
    };
};

