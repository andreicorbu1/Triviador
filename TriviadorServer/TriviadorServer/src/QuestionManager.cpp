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

void QuestionManager::AddQuestion(const NumericalAnswerQuestion& question)
{
	m_storage.insert(question);
}

void QuestionManager::PopulateStorage()
{
	if (m_storage.count<MultipleAnswerQuestion>() == 0 && m_storage.count<NumericalAnswerQuestion>() == 0)
	{
		std::ifstream fin;
		fin.open("resource/multipleAnswerQuestions.txt");
		while (!fin.eof())
		{
			MultipleAnswerQuestion multipelAnswerQuestion;
			fin >> multipelAnswerQuestion;
			AddQuestion(multipelAnswerQuestion);
			
		}
		fin.close();
		fin.open("resource/numericalAnswerQuestions.txt");
		while (!fin.eof())
		{
			NumericalAnswerQuestion numericalAnswerQuestion;
			fin >> numericalAnswerQuestion;
			AddQuestion(numericalAnswerQuestion);
		}
		fin.close();
	}
}

