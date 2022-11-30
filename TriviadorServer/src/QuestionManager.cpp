#include "QuestionManager.h"

QuestionManager::QuestionManager(const std::string& path)
    : m_storage(CreateStorageForQuestions(path))
{
    m_storage.sync_schema();
}

void QuestionManager::AddQuestion(const MultipleAnswerQuestion& question)
{
    m_storage.insert(question);
}
