#include "QuestionManager.h"

QuestionManager::QuestionManager(QWidget* parent)
    : m_questionWindow(new QuestionWindow(parent))
{
    // empty   
}

QuestionManager::~QuestionManager()
{
    // empty
}

void QuestionManager::ShowMultipleAnswerQuestion()
{
    m_questionWindow->SetQuestionType(QuestionType::MultipleAnswer);
    m_questionWindow->show();
    m_questionWindow->StartTimer();
}

void QuestionManager::ShowNumericalAnswerQuestion()
{
    m_questionWindow->SetQuestionType(QuestionType::NumericalAnswer);
    m_questionWindow->show();
    m_questionWindow->StartTimer();
}
