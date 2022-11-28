#include "QuestionManager.h"

QuestionManager::QuestionManager()
{
}

void QuestionManager::AddQuestion(Question<std::string> s)
{
	db.insert(s);
}
