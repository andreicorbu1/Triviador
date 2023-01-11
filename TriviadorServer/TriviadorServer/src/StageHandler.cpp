#include "StageHandler.h"

StageHandler::StageHandler(Game& game):
	m_game(game)
{
}

crow::response StageHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto playerWhoSentRequest = bodyArgs.find("username");
	if(playerWhoSentRequest!=end)
	{
		std::string username = playerWhoSentRequest->second;
		std::unordered_set<std::string> playersWhoSentRequest = m_game.GetPlayersWhoSentRequest();
		//if (!playersWhoSentRequest.contains(username))
		//{
		//	m_game.AddPlayerWhoSentRequest(username);
		//	std::unordered_set<std::string> playersWhoSentRequest = m_game.GetPlayersWhoSentRequest();
		//	//if (playersWhoSentRequest.size() == m_game.GetPlayers().size())  //temporary
		//	//{
		//	//	m_game.GoToNextStage();
		//	//}
		//}
		//else
		//{
		//	return crow::json::wvalue
		//	{
		//		{"state", "wait"}
		//	};
		//}
		std::string currentStage = m_game.GetCurrentStage();
		std::cout << currentStage;
		crow::json::wvalue response
		{
			{"stage", currentStage}
		};
		return response;
	}
	return crow::response(401, "NO USERNAME");
}
