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
		
		std::string currentStage = m_game.GetCurrentStage();
		if (currentStage == "chooseBase")
		{
			if (username == m_game.GetPlayerWhoWillMakeAChoice())
			{
				crow::json::wvalue response
				{
					{"stage", currentStage}
				};
				return response;
			}
			else
			{
				crow::json::wvalue response
				{
					{"stage", "wait"}
				};
				return response;
			}
		}
		std::cout << currentStage;
		crow::json::wvalue response
		{
			{"stage", currentStage}
		};
		return response;
	}
	return crow::response(401, "NO USERNAME");
}
