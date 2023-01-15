#include "MultipleAnswerQuestionHandler.h"

MultipleAnswerQuestionHandler::MultipleAnswerQuestionHandler(Game& game) : m_game(game)
{}

crow::json::wvalue MultipleAnswerQuestionHandler::ToJson(const MultipleAnswerQuestion& question, const crow::json::wvalue& players, const crow::json::wvalue& answers, int id) const
{
	crow::json::wvalue questionJson
	{
		{"question", question.GetQuestion()},
		{"right_answer", question.GetRightAnswer()},
		{"answers", answers},
		{"id", id},
		{"players", players}
	};
	return crow::json::wvalue(questionJson);
}

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
				playersWhoSentRequest = m_game.GetPlayersWhoSentRequest();
				if (playersWhoSentRequest.size() == m_game.GetPlayers().size())
				{
					m_game.IncrementMultipleAnswerQuestionIndex();
				}
			}
			else
			{
				return crow::response(402, "Player already did this request");
			}
			std::random_device rd;
			std::mt19937 g(rd());
			std::vector <crow::json::wvalue> answersJson;
			auto answers = multipleAnswerQuestion.GetAnswers();
			std::ranges::shuffle(answers, g);
			for (auto& answer : answers)
			{
				answersJson.push_back(crow::json::wvalue(answer));
			}

			std::vector<Player> playersWhoCanAskTheQuestion = m_game.GetParticipants();
			nlohmann::json json = playersWhoCanAskTheQuestion;

			if (playersWhoCanAskTheQuestion.empty())
			{
				return crow::response(400);
			}

			std::string jsonString = json.dump();
			crow::json::wvalue playersJson = crow::json::wvalue(crow::json::load(jsonString));

			return ToJson(multipleAnswerQuestion, playersJson, answersJson, id);
		}
		catch (const std::exception& e)
		{
			return crow::response(400);
		}
	}
	return crow::response(401, "NO USERNAME");
}
