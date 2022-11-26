#include "QuestionsIntoDataBase.h"


auto QuestionsIntoDataBase::createStorage(const std::string& databaseFileName, const MultipleAnswerQuestion& multipleAnswerQuestion)
{
	return sql::make_storage(
		databaseFileName,
		sql::make_table(
			"Multiple Answer Questions",
			sql::make_column("id", &MultipleAnswerQuestion::m_id, sql::autoincrement(), sql::primary_key()),
			sql::make_column("Question", &MultipleAnswerQuestion::m_question),
			sql::make_column("Right Answer", &MultipleAnswerQuestion::m_rightAnswer)
			sql::make_column("Answer Options", &MultipleAnswerQuestion::m_answers),

		),
		sql::make_table(
			"ShoppingBasket",
			sql::make_column("id", &ShoppingBasketRow::id, sql::autoincrement(), sql::primary_key()),
			sql::make_column("idProduct", &ShoppingBasketRow::idProduct),
			sql::make_column("quantity", &ShoppingBasketRow::quantity)
		)
	);
}
