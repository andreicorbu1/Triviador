#include "AddToAcountListHandler.h"
#include "LoginHandler.h"
#include "NumericalAnswerQuestionHandler.h"
#include "MultipleAnswerQuestionHandler.h"
#include "CreateLobbyHandler.h"
#include "CreateGameHandler.h"
#include "AddToLobbyHandler.h"
#include "RemoveFromLobbyHandler.h"
#include "WaitingInLobbyHandler.h"
#include "GetAllPlayersFromLobbyHandler.h"
#include "MultipleAnswerQuestion.h"
#include "QuestionManager.h"
#include "Game.h"

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

	Lobby lobby;
	auto& createNewLobby = CROW_ROUTE(app, "/newlobby");
	createNewLobby(CreateLobbyHandler(lobby, userList));

	auto& addToLobby = CROW_ROUTE(app, "/addplayertolobby").methods(crow::HTTPMethod::PUT);
	addToLobby(AddToLobbyHandler(lobby, userList));

	auto& waitInLobby = CROW_ROUTE(app, "/waitinginlobby");
	waitInLobby(WaitingInLobbyHandler(lobby));

	auto& removePlayerFromLobby = CROW_ROUTE(app, "/removeplayerfromlobby");
	removePlayerFromLobby(RemoveFromLobbyHandler(lobby, userList));

	auto& getPlayersFromLobby= CROW_ROUTE(app, "/getplayersfromlobby");
	getPlayersFromLobby(GetAllPlayersFromLobbyHandler(lobby));

	//for testing route
	//CROW_ROUTE(app, "/numberOfLobbies")([&onGoingLobbies]()
	//	{
	//		crow::json::wvalue numberOfLobbies
	//	{
	//		{"number of lobbies", onGoingLobbies.size()}
	//	};
	//return crow::json::wvalue(numberOfLobbies);
	//	});

	////for testing route
	//CROW_ROUTE(app, "/numberOfPlayersFromLobby/<int>")([&onGoingLobbies](int lobbyID)
	//	{
	//		if (onGoingLobbies.contains(lobbyID))
	//		{
	//			crow::json::wvalue numberOfPlayersFromLobby
	//			{
	//				{"number of players in current lobby", onGoingLobbies[lobbyID].GetNumberOfPlayers()}
	//			};
	//			return crow::json::wvalue(numberOfPlayersFromLobby);
	//		}
	//crow::json::wvalue lobbyNotFound
	//{
	//	{"lobby not found",""}
	//};
	//return lobbyNotFound;
	//	});

	//auto& createNewGame = CROW_ROUTE(app, "/newgame/<int>").methods(crow::HTTPMethod::PUT);
	//createNewGame(CreateGameHandler(ongoingGames));

	app.port(18080).multithreaded().run();
	return 0;
}
