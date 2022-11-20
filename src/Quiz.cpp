#include "Quiz.h"

Quiz::Quiz()
{
	ReadFromFile("res\\NumericalAnswerQuestions.txt");
	ReadFromFile("res\\MultipleAnswerQuestions.txt", false);
}

Quiz::Quiz(const std::unordered_set<NumericalAnswerQuestion<int>, HashFunctionForNumericalQuestion>& numericalAnswerQuestions,
	const std::unordered_set<MultipleAnswerQuestion, HashFunctionForMultipleAnswerQuestion>& multipleAnswerQuestion) :
	m_numericalAnswerQuestions(numericalAnswerQuestions),
	m_multipleAnswerQuestions(multipleAnswerQuestion)
{
	ReadFromFile("res\\NumericalAnswerQuestions.txt");
	ReadFromFile("res\\MultipleAnswerQuestions.txt", false);
}

size_t Quiz::HashFunctionForNumericalQuestion::operator()(const NumericalAnswerQuestion<int>& numericalAnswerQuestion) const
{
	size_t hashValue = numericalAnswerQuestion.GetRightAnswer() ^ numericalAnswerQuestion.GetQuestion().size();
	return hashValue;
}

size_t Quiz::HashFunctionForMultipleAnswerQuestion::operator()(const MultipleAnswerQuestion& multipleAnswerQuestion) const
{
	size_t hashValue = multipleAnswerQuestion.GetRightAnswer().size() ^ multipleAnswerQuestion.GetQuestion().size();
	return hashValue;
}

void Quiz::SetNumericalAnswerQuestions(const std::unordered_set<NumericalAnswerQuestion<int>,
	HashFunctionForNumericalQuestion>& numericalAnswerQuestions)
{
	m_numericalAnswerQuestions = numericalAnswerQuestions;
}

void Quiz::SetMultipleAnswerQuestions(const std::unordered_set<MultipleAnswerQuestion,
	HashFunctionForMultipleAnswerQuestion>& multipleAnswerQuestions)
{
	m_multipleAnswerQuestions = multipleAnswerQuestions;
}

const std::unordered_set<NumericalAnswerQuestion<int>, Quiz::HashFunctionForNumericalQuestion>& Quiz::
GetNumericalAnswerQuestions() const
{
	return m_numericalAnswerQuestions;
}

const std::unordered_set<MultipleAnswerQuestion, Quiz::HashFunctionForMultipleAnswerQuestion>& Quiz::
GetMultipleAnswerQuestions() const
{
	return m_multipleAnswerQuestions;
}

void Quiz::ReadFromFile(std::string fileName, bool readNumericalAnswerQuestion)
{
	std::ifstream fin;
	fin.open(fileName);
	if (fin) {
		if (readNumericalAnswerQuestion) {
			while (!fin.eof()) {
				NumericalAnswerQuestion<int> numericalAnswerQuestion;
				fin >> numericalAnswerQuestion;
				m_numericalAnswerQuestions.insert(numericalAnswerQuestion);
			}
		}
		else
		{
			while (!fin.eof()) {
				MultipleAnswerQuestion multipleAnswerQuestion;
				fin >> multipleAnswerQuestion;
				m_multipleAnswerQuestions.insert(multipleAnswerQuestion);
			}
		}
	}
}

void Quiz::Start()
{
	uint16_t op = 1;
	std::cout << "\nAlege tip intrebare: ";
	std::cout << "\n1. Intrebare cu un singur raspuns numeric";
	std::cout << "\n2. Intrebare cu mai multe variante de raspuns\n";

	std::cout << "Alege tip: ";
	std::cin >> op;
	if (op == 1)
	{
		auto it = m_numericalAnswerQuestions.begin();
		while (op != 0 && it != m_numericalAnswerQuestions.end())
		{
			std::cout << *it;
			std::cout << "\nSelecteaza raspunsul corect: ";
			int answer;
			std::cin >> answer;
			if (answer == it->GetRightAnswer())
			{
				std::cout << "\nRaspunsul este corect";
			}
			else
			{
				std::cout << "\nRaspunsul este gresit";
				std::cout << "\nRaspunsul corect era: " << it->GetRightAnswer();
			}
			it++;
			std::cout << "\nCiteste un intreg diferit de zero daca doresti sa continui: ";
			std::cin >> op;
			if (it == m_numericalAnswerQuestions.end())
			{
				std::cout << "\nAi parcurs toate intrebarile";
			}
		}
	}
	else
	{
		auto it = m_multipleAnswerQuestions.begin();
		while (op != 0 && it != m_multipleAnswerQuestions.end())
		{
			std::cout << *it;
			std::cout << "\nSelecteaza raspunsul corect: ";
			int answer;
			std::cin >> answer;
			if (it->GetRightAnswer() == it->GetAnswers()[answer - 1])
			{
				std::cout << "\nRaspunsul este corect";
			}
			else
			{
				std::cout << "\nRaspunsul este gresit";
			}
			it++;
			std::cout << "\nCiteste un intreg diferit de zero daca doresti sa continui: ";
			std::cin >> op;
		}
		if (it == m_multipleAnswerQuestions.end())
		{
			std::cout << "\nAi parcurs toate intrebarile";
		}
	}
}


