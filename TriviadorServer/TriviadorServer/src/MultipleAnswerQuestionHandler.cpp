#include "MultipleAnswerQuestionHandler.h"

MultipleAnswerQuestionHandler::MultipleAnswerQuestionHandler(Game& game) : m_game(game)
{}

crow::response MultipleAnswerQuestionHandler::operator()(const crow::request& req) const
{
	try
	{
		auto [question, id] = m_game.GetMultipleAnswerQuestion();
		std::vector <crow::json::wvalue> answersJson;
		for (auto& answer : question.GetAnswers())
		{
			answersJson.push_back(crow::json::wvalue(answer));
		}

		crow::json::wvalue questionJson
		{
			{"question", question.GetQuestion()},
			{"right_answer", question.GetRightAnswer()},
			{"answers", answersJson},
			{"id", id}
		};
		return crow::json::wvalue(questionJson);
	}
	catch (const std::exception& e)
	{
		return crow::response(400);
	}
}
