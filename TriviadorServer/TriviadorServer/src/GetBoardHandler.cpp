#include "GetBoardHandler.h"

GetBoardHandler::GetBoardHandler(Game& game) : m_game(game)
{
}

crow::response GetBoardHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto playerWithRequest = bodyArgs.find("username");
	if (playerWithRequest != end) {
		std::string username = playerWithRequest->second;
		std::unordered_set<std::string> playersWhoSentRequest = m_game.GetPlayersWhoSentRequest();
		if (!playersWhoSentRequest.contains(username))
		{
			m_game.AddPlayerWhoSentRequest(username);
			playersWhoSentRequest = m_game.GetPlayersWhoSentRequest();
			if (playersWhoSentRequest.size() == m_game.GetPlayers().size())
			{
				m_game.GoToNextStage();
			}
			Board board = m_game.GetBoard();
			std::vector<Territory> territories = board.GetTerritories();
			nlohmann::json json = territories;

			if (json.empty())
			{
				return crow::response(400);
			}

			std::string jsonString = json.dump();
			//std::cout << jsonString;
			return crow::json::wvalue(crow::json::load(jsonString));
		}
	}
}
