#include "ChooseHandler.h"

ChooseHandler::ChooseHandler(Game& game):
	m_game(game)
{
}

crow::response ChooseHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto userName = bodyArgs.find("username");
	auto boardPosition = bodyArgs.find("position");
	auto base = bodyArgs.find("isBase");
	if (userName != end && boardPosition!=end)
	{
		std::string username = userName->second;
		int position = std::stoi(boardPosition->second);
		bool isBase = std::stoi(base->second.c_str());
		if (m_game.AddTerritory(username, position, isBase))
		{
			m_game.PopPlayerWhoWillMakeAChoose();
			m_game.GoToNextStage();
			return crow::response(200, "Successfully added base");
		}
		return crow::response(402, "Occupied position/Game doesn't have a player with that user");
	}
	return crow::response(401, "Invalid username or position");
}
