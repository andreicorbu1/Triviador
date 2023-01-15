#include "GetAllPlayersFromGameHandler.h"

GetAllPlayersFromGameHandler::GetAllPlayersFromGameHandler(Game& game) : m_game(game)
{
}

crow::response GetAllPlayersFromGameHandler::operator()(const crow::request& req) const
{
	m_game.DetermineScoreForAllPlayers();
	std::vector<Player>& players = m_game.GetPlayers();
	nlohmann::json json = players;

	if (players.empty())
	{
		return crow::response(400);
	}
	
	std::string jsonString = json.dump();
	return crow::json::wvalue(crow::json::load(jsonString));
}
