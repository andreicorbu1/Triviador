#include "AttackTerritoryHandler.h"

AttackTerritoryHanndler::AttackTerritoryHanndler(Game& game) : m_game(game)
{
}

crow::response AttackTerritoryHanndler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto playerWhoSentRequest = bodyArgs.find("username");
	auto territoryAttacked = bodyArgs.find("position");
	if (m_game.GetCurrentStage() == "attack" && playerWhoSentRequest != end && territoryAttacked != end)
	{
		std::string username = playerWhoSentRequest->second;
		Player attacker;
		for (const auto& player : m_game.GetPlayers())
		{
			if (player.GetName() == username)
			{
				attacker = player;
				break;
			}
		}
		size_t position = std::stoi(territoryAttacked->second);
		size_t width = m_game.GetBoard().GetWidth();
		Territory attackedTerritory = m_game.GetBoard()[{position / width, position% width}];
		if (attackedTerritory.GetOwner().has_value())
		{
			m_game.AddPlayerToDuel(attacker);
			m_game.AddPlayerToDuel(attackedTerritory.GetOwner().value());
			m_game.GoToNextStage();
			return crow::response(200);
		}
		else
		{
			return crow::response(400, "Territory doesn't have an owner, please choose another territory");
		}
	}
	else
	{
		return crow::response(404, "Request not correct");
	}
}