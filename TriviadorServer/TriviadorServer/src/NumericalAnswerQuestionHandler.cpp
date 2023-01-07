#include "NumericalAnswerQuestionHandler.h"

NumericalAnswerQuestionHandler::NumericalAnswerQuestionHandler(Game& game) : m_game(game)
{}

crow::response NumericalAnswerQuestionHandler::operator()(const crow::request& req) const
{
	try
	{
		auto [question, id] = m_game.GetNumericalAnswerQuestion();
		crow::json::wvalue questionJson
		{
			{"question", question.GetQuestion()},
			{"right_answer", question.GetRightAnswer()},
			{"id", id}
		};
		return questionJson;
	}
	catch (const std::exception& e)
	{
		return crow::response(400);
	}
}
