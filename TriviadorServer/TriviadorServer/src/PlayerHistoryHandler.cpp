#include "PlayerHistoryHandler.h"

PlayerHistoryHandler::PlayerHistoryHandler(PlayerHistoryManager& playerHistoryManager)
	:m_playerHistoryManager(playerHistoryManager)
{
}

crow::response PlayerHistoryHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto username = bodyArgs.find("username");
	if (username == end)
	{
		crow::json::wvalue noUsername
		{
			{"invalid_username", "No username"}
		};
		return crow::json::wvalue(noUsername);
	}
	try 
	{
		std::vector<PlayerHistory> playerHistory = m_playerHistoryManager.GetPlayerMatches(username->second);
		nlohmann::json json = playerHistory;
		if (playerHistory.empty())
		{
			crow::json::wvalue noMatchHistory
			{
				{"game", "No games played!"}
			};
			return crow::json::wvalue(noMatchHistory);
		}
		std::string jsonString = json.dump();
		return crow::json::wvalue(crow::json::load(jsonString));
		

	}
	catch (const std::exception& e)
	{
		return crow::response(400);
	}
}
