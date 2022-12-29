#include "AddToAcountListHandler.h"
#include "LoginHandler.h"
#include "NumericalAnswerQuestionHandler.h"
#include "MultipleAnswerQuestionHandler.h"
#include "CreateLobbyHandler.h"
#include "CreateGameHandler.h"
#include "MultipleAnswerQuestion.h"
#include "AddToLobbyHandler.h"
#include "QuestionManager.h"
#include "Game.h"
#include "Lobby.h"
#include <crow.h>

int main()
{
	AccountManager userList("resource/Accounts.sqlite");
	QuestionManager questionManager("resource/Questions.sqlite");
	questionManager.PopulateStorage();

	crow::SimpleApp app;

	auto& addUserToAccountList = CROW_ROUTE(app, "/signup").methods(crow::HTTPMethod::PUT);
	addUserToAccountList(AddAccountHandler(userList));

	auto& loginToAccount = CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::POST);
	loginToAccount(LoginHandler(userList));

	auto& getMultipleAnswerQuestion = CROW_ROUTE(app, "/MultipleAnswerQuestion");
	getMultipleAnswerQuestion(MultipleAnswerQuestionHandler(questionManager));

	auto& getNumericalAnswerQuestion = CROW_ROUTE(app, "/NumericalAnswerQuestion");
	getNumericalAnswerQuestion(NumericalAnswerQuestionHandler(questionManager));

	std::unordered_map<uint32_t, Lobby> onGoingLobbies;
	auto& createNewLobby = CROW_ROUTE(app, "/newlobby");
	createNewLobby(CreateLobbyHandler(onGoingLobbies));

	auto& addToLobby = CROW_ROUTE(app, "/addplayertolobby").methods(crow::HTTPMethod::PUT);
	addToLobby(AddToLobbyHandler(onGoingLobbies));

	//CROW_ROUTE(app, "/addToLobby/<int>")([&onGoingLobbies](int lobbyID)
	//	{
	//		if (onGoingLobbies.contains(lobbyID))
	//		{
	//			if (onGoingLobbies[lobbyID].GetNumberOfPlayers() < 4)
	//			{
	//				onGoingLobbies[lobbyID].AddPlayer();
	//				return crow::response(200, "Successfully Added Player to Lobby");
	//			}
	//			return crow::response(401, "Full lobby");
	//		}
	//return crow::response(400, "Lobby not found");
	//	});

	//for testing route
	CROW_ROUTE(app, "/numberOfLobbies")([&onGoingLobbies]()
		{
			crow::json::wvalue numberOfLobbies
		{
			{"number of lobbies", onGoingLobbies.size()}
		};
	return crow::json::wvalue(numberOfLobbies);
		});

	//for testing route
	CROW_ROUTE(app, "/numberOfPlayersFromLobby/<int>")([&onGoingLobbies](int lobbyID)
		{
			if (onGoingLobbies.contains(lobbyID))
			{
				crow::json::wvalue numberOfPlayersFromLobby
				{
					{"number of players in current lobby", onGoingLobbies[lobbyID].GetNumberOfPlayers()}
				};
				return crow::json::wvalue(numberOfPlayersFromLobby);
			}
	crow::json::wvalue lobbyNotFound
	{
		{"lobby not found",""}
	};
	return lobbyNotFound;
		});

	//auto& createNewGame = CROW_ROUTE(app, "/newgame/<int>").methods(crow::HTTPMethod::PUT);
	//createNewGame(CreateGameHandler(ongoingGames));

	app.port(18080).multithreaded().run();
	return 0;
}
