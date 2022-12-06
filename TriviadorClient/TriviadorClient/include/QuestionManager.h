#pragma once

#include <QuestionWindow.h>

class QuestionManager
{
public:
    QuestionManager(QWidget* parent = nullptr);
    ~QuestionManager();
    
    void ShowMultipleAnswerQuestion();
    void ShowNumericalAnswerQuestion();
    
private:
    QuestionWindow* m_questionWindow;
};

