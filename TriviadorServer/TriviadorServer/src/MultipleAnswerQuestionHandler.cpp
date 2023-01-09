#include "MultipleAnswerQuestionHandler.h"

MultipleAnswerQuestionHandler::MultipleAnswerQuestionHandler(Game& game) : m_game(game)
{}

crow::response MultipleAnswerQuestionHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto playerWhoSentRequest = bodyArgs.find("username");
	if (playerWhoSentRequest != end)
	{
		try
		{
			std::string username = playerWhoSentRequest->second;
			std::unordered_set<std::string> playersWhoSentRequest = m_game.GetPlayersWhoSentRequest();
			MultipleAnswerQuestion multipleAnswerQuestion;
			int id;
			if (!playersWhoSentRequest.contains(username))
			{
				multipleAnswerQuestion = m_game.GetCurrentMultipleAnswerQuestion();
				id = m_game.GetCurrentMultipleAnswerQuestionIndex();
				m_game.AddPlayerWhoSentRequest(username);

			}
			else if(playersWhoSentRequest.size()==m_game.GetPlayers().size())
			{
				std::pair<MultipleAnswerQuestion, uint16_t> questionFromServer = m_game.GetNewMultipleAnswerQuestion();
				multipleAnswerQuestion = questionFromServer.first;
				id = questionFromServer.second;
				m_game.AddPlayerWhoSentRequest(username);
			}
			else
			{
				return crow::response(402, "Player already did this request");
			}

			std::vector <crow::json::wvalue> answersJson;
			for (auto& answer : multipleAnswerQuestion.GetAnswers())
			{
				answersJson.push_back(crow::json::wvalue(answer));
			}

			crow::json::wvalue questionJson
			{
				{"question", multipleAnswerQuestion.GetQuestion()},
				{"right_answer", multipleAnswerQuestion.GetRightAnswer()},
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
	return crow::response(401, "NO USERNAME");
}
