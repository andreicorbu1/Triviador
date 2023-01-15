#include "StageHandler.h"

StageHandler::StageHandler(Game& game, AccountManager& userList):
	m_game(game),
	m_userList(userList)
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
		if (currentStage == "chooseBase" || currentStage=="chooseTerritory")
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
				std::cout << currentStage;
				crow::json::wvalue response
				{
					{"stage", "wait"}
				};
				return response;
			}
		}
		else if(currentStage=="attack" && username != m_game.GetCurrentAttacker().GetName())
		{
				currentStage = "wait";
		}
		else if (currentStage == "result")
		{
			m_game.AddPlayerWhoSentRequest(username);
			m_game.UpdateGameHistory(username);
			m_userList.InsertUsersFromDbInAccounts();
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