#include <filesystem>
#include <iostream>
#include <memory>
#include <sqlite_orm/sqlite_orm.h>
#include "Question.h"
#include "MultipleAnswerQuestion.h"
#include "NumericalAnswerQuestion.h"
#include "QuestionsIntoDataBase.h"
namespace sql = sqlite_orm;
auto createStorage(const std::string& databaseFileName)
{
	return sql::make_storage(
		databaseFileName,
		sql::make_table(
		"Multiple Answer Questions",
		sql::make_column("id", &MultipleAnswerQuestion::m_id, sql::autoincrement(), sql::primary_key()),
		sql::make_column("Question", &MultipleAnswerQuestion::m_question),
		sql::make_column("Right Answer", &MultipleAnswerQuestion::m_rightAnswer),
		sql::make_column("Answer Options 1", &MultipleAnswerQuestion::m_answers)
	)
	);
}
using Storage = decltype(createStorage(""));

int main()
{
	//std::cout << "Hello World!\n";
	Question<std::string>* question;
	Question<int>* question2;
	MultipleAnswerQuestion maq;
	NumericalAnswerQuestion naq;
	std::cin >> maq;
	//std::cin >> naq;
	Storage testDatabase = createStorage("test.sqlite");
	question = new MultipleAnswerQuestion(maq);
	question2 = new NumericalAnswerQuestion(naq);
	std::cout << maq;
	std::cout << naq;
}
