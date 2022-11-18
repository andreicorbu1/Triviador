#include "Quiz.h"

Quiz::Quiz()
{
	ReadFromFile("NumericalAnswerQuestion.txt");
	//ReadFromFile("MultipleAnswerQuestion.txt");
}

Quiz::Quiz(const std::unordered_set<NumericalAnswerQuestion<int>, HashFunctionForNumericalQuestion>& numericalAnswerQuestions,
	const std::unordered_set<MultipleAnswerQuestion, HashFunctionForMultipleAnswerQuestion>& multipleAnswerQuestion) :
	m_numericalAnswerQuestions(numericalAnswerQuestions),
	m_multipleAnswerQuestions(multipleAnswerQuestion)
{
	ReadFromFile("NumericalAnswerQuestion.txt");
	//ReadFromFile("MultipleAnswerQuestion.txt");
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
	std::cout << "1. Intrebare cu un singur raspuns numeric\n";
	std::cout << "2. Intrebare cu mai multe variante de raspuns\n";

	std::cin >> op;
	if (op == 1)
	{
		//
	}
	while (op)
	{

	}
}


