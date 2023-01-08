#include "GetBoardHandler.h"

GetBoardHandler::GetBoardHandler(Game& game) : m_game(game)
{
}

crow::response GetBoardHandler::operator()(const crow::request& req) const
{
	Board board = m_game.GetBoard();
	std::vector<Territory> territories = board.GetTerritories();
	nlohmann::json json = territories;

	if (json.empty())
	{
		return crow::response(400);
	}

	std::string jsonString = json.dump();
	return crow::json::wvalue(crow::json::load(jsonString));
}
