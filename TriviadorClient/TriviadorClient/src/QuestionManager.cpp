#include "QuestionManager.h"

QuestionManager::QuestionManager()
{
    // empty
}

QuestionManager::~QuestionManager()
{
    // empty
}

void QuestionManager::SetParentWidget(QWidget* parent)
{
    m_parent = parent;
}
void QuestionManager::ShowMultipleAnswerQuestion()
{
    Question* question = new Question(m_parent, QuestionType::MultipleAnswer);
    question->show();
    question->StartTimer();
}

void QuestionManager::ShowNumericalAnswerQuestion()
{
    Question* question = new Question(m_parent, QuestionType::NumericalAnswer);
    question->show();
    question->StartTimer();
}
