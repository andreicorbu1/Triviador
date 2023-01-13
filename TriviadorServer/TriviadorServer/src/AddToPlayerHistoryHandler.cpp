#include "AddToPlayerHistoryHandler.h"

AddToPlayerHistoryHandler::AddToPlayerHistoryHandler(PlayerHistoryManager& playerHistoryManager)
	:m_playerHistoryManager(playerHistoryManager)
{
}

crow::response AddToPlayerHistoryHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto gameID = bodyArgs.find("id");
	auto username = bodyArgs.find("username");
	auto score = bodyArgs.find("score");
	auto rank = bodyArgs.find("rank");
	
	if (gameID == end || username == end || score == end || rank == end)
	{
		return crow::response(400);
	}
		
	PlayerHistory playerHistory;
	playerHistory.SetID(std::stoi(gameID->second));
	playerHistory.SetScore(std::stoi(score->second));
	playerHistory.SetUsername(username->second);
	playerHistory.SetRank(std::stoi(rank->second));
	m_playerHistoryManager.AddPlayerHistory(playerHistory);
	
	return crow::response(200, "Successfully Added Player History!");
}
