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
	catch(std::system_error e)
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
		std::cout << "ID: " << numericalAnswerQuestion.GetId() << " " << e.what()<<"\n";
	}
}

const MultipleAnswerQuestion& QuestionManager::GetMultipleAnswerQuestion(int id)
{
	try
	{
		return m_storage.get<MultipleAnswerQuestion>(id);
	}
	catch (std::system_error e)
	{
		std::cout <<"ID: " <<id<<" "<< e.what() << "\n";
		return MultipleAnswerQuestion();
	}
}

const NumericalAnswerQuestion& QuestionManager::GetNumericalAnswerQuestion(int id)
{
	try
	{
		return m_storage.get<NumericalAnswerQuestion>(id);
	}
	catch (std::system_error e)
	{
		std::cout << "ID: " << id << " " << e.what() << "\n";
		return NumericalAnswerQuestion();
	}
}

const MultipleAnswerQuestion& QuestionManager::GetRandomMultipleAnswerQuestion()
{
	auto multipleAnswerQuestion = m_storage.get<MultipleAnswerQuestion>(GetRandomMultipleAnswerQuestionsID());
	return multipleAnswerQuestion;
}

int QuestionManager::GetRandomMultipleAnswerQuestionsID()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(1, m_storage.count<MultipleAnswerQuestion>());
	int id = distr(eng);
	while(alreadyChoosedMultipleAnswerQuestionsID.contains(id))
	{
		id = distr(eng);
	}
	return id;
}

int QuestionManager::GetRandomNumericalAnswerQuestionsID()
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(1, m_storage.count<NumericalAnswerQuestion>());
	int id = distr(eng);
	while (!alreadyChoosedNumericalAnswerQuestionsID.contains(id))
	{
		id = distr(eng);
	}
	return id;
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
