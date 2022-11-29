#include "QuestionManager.h"

QuestionManager::QuestionManager(const std::string& path)
    : m_storage(CreateStorageForQuestions(path))
{
    m_storage.sync_schema();
}

void QuestionManager::AddQuestion(MultipleAnswerQuestion& s)
{
    m_storage.insert(s);
}
