#include "QuestionManager.h"

QuestionManager::QuestionManager(const std::string& path = "resource/Questions.sqlite")
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

void QuestionManager::RemoveMultipleAnswerQuestion(int id)
{
	m_storage.remove<MultipleAnswerQuestion>(id);
}

void QuestionManager::RemoveNumericalAnswerQuestion(int id)
{
	m_storage.remove<NumericalAnswerQuestion>(id);
}

void QuestionManager::UpdateQuestion(const MultipleAnswerQuestion& multipleAnswerQuestion)
{
	try
	{
		m_storage.get<MultipleAnswerQuestion>(multipleAnswerQuestion.GetId());
		m_storage.replace(multipleAnswerQuestion);
	}
	catch (std::system_error e)
	{
		std::cout << "ID: " << multipleAnswerQuestion.GetId() << " " << e.what() << "\n";
	}
}

void QuestionManager::UpdateQuestion(const NumericalAnswerQuestion& numericalAnswerQuestion)
{
	try
	{
		m_storage.get <NumericalAnswerQuestion>(numericalAnswerQuestion.GetId());
		m_storage.replace(numericalAnswerQuestion);
	}
	catch (std::system_error e)
	{
		std::cout << "ID: " << numericalAnswerQuestion.GetId() << " " << e.what() << "\n";
	}
}

MultipleAnswerQuestion QuestionManager::GetMultipleAnswerQuestion(int id)
{
	try
	{
		return m_storage.get<MultipleAnswerQuestion>(id);
	}
	catch (std::system_error e)
	{
		std::cout << "ID: " << id << " " << e.what() << "\n";
	}
}

NumericalAnswerQuestion QuestionManager::GetNumericalAnswerQuestion(int id)
{
	try
	{
		return m_storage.get<NumericalAnswerQuestion>(id);
	}
	catch (std::system_error e)
	{
		std::cout << "ID: " << id << " " << e.what() << "\n";
	}
}

int QuestionManager::GetRandomMultipleAnswerQuestionsID()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(1, m_storage.count<MultipleAnswerQuestion>());
	int id = distr(eng);
	while (m_alreadyChoosedMultipleAnswerQuestionsID.contains(id))
	{
		id = distr(eng);
	}
	m_alreadyChoosedMultipleAnswerQuestionsID.insert(id);
	return id;
}

int QuestionManager::GetRandomNumericalAnswerQuestionsID()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(1, m_storage.count<NumericalAnswerQuestion>());
	int id = distr(eng);
	while (m_alreadyChoosedNumericalAnswerQuestionsID.contains(id))
	{
		id = distr(eng);
	}
	m_alreadyChoosedNumericalAnswerQuestionsID.insert(id);
	return id;
}

void QuestionManager::Clear()
{
	m_alreadyChoosedMultipleAnswerQuestionsID.clear();
	m_alreadyChoosedNumericalAnswerQuestionsID.clear();
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
