#include "NumericalAnswerQuestionHandler.h"

NumericalAnswerQuestionHandler::NumericalAnswerQuestionHandler(Game& game) : m_game(game)
{}

crow::json::wvalue NumericalAnswerQuestionHandler::to_json(const NumericalAnswerQuestion& question, const crow::json::wvalue& playersJson, uint16_t id) const
{
	crow::json::wvalue questionJson
	{
		{"question", question.GetQuestion()},
		{"right_answer", question.GetRightAnswer()},
		{"id", id},
		{"players", playersJson}
	};
	return questionJson;
}

crow::response NumericalAnswerQuestionHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto playerWhoSentRequest = bodyArgs.find("username");
	if (playerWhoSentRequest != end) {
		try
		{
			std::string username = playerWhoSentRequest->second;
			std::unordered_set<std::string> playersWhoSentRequest = m_game.GetPlayersWhoSentRequest();
			NumericalAnswerQuestion question;
			uint16_t id;
			if (!playersWhoSentRequest.contains(username))
			{
				m_game.AddPlayerWhoSentRequest(username);
				question = m_game.GetCurrentNumericalAnswerQuestion();
				id = m_game.GetCurrentNumericalAnswerQuestionIndex();
			}
			else if(playersWhoSentRequest.size()==m_game.GetPlayers().size())
			{
				//auto [question, id] = m_game.GetNumericalAnswerQuestion();
				std::pair<NumericalAnswerQuestion, uint16_t>questionFromServer = m_game.GetNewNumericalAnswerQuestion();
				question = questionFromServer.first;
				id = questionFromServer.second;
				m_game.AddPlayerWhoSentRequest(username);
			}
			else
			{
				return crow::response(402, "Player already did this request");
			}
			std::vector<Player>playersWhoCanAskTheQuestion = m_game.GetParticipants();
			nlohmann::json playersWhoCanAskTheQuestionJson = playersWhoCanAskTheQuestion;

			std::string jsonString = playersWhoCanAskTheQuestionJson.dump();
			crow::json::wvalue json = crow::json::wvalue(crow::json::load(jsonString));

			return to_json(question, json, id);
		}
		catch (const std::exception& e)
		{
			return crow::response(400);
		}
	}
	return crow::response(401, "NO USERNAME");
}
