#include "AddToAcountListHandler.h"
#include "LoginHandler.h"
#include "NumericalAnswerQuestionHandler.h"
#include "MultipleAnswerQuestionHandler.h"
#include "CreateLobbyHandler.h"
#include "CreateGameHandler.h"
#include "AddToLobbyHandler.h"
#include "RemoveFromLobbyHandler.h"
#include "WaitingInLobbyHandler.h"
#include "MultipleAnswerQuestion.h"
#include "SendAnswerMultipleQuestion.h"
#include "SendAnswerNumericalQuestion.h"
#include "QuestionManager.h"
#include "Game.h"

int main()
{
	AccountManager userList("resource/Accounts.sqlite");
	QuestionManager questionManager("resource/Questions.sqlite");
	questionManager.PopulateStorage();
	Game currentGame({Player("Andrei", Player::Color::Blue), Player("Adi", Player::Color::Red)});
	crow::SimpleApp app;

	auto& addUserToAccountList = CROW_ROUTE(app, "/signup").methods(crow::HTTPMethod::PUT);
	addUserToAccountList(AddAccountHandler(userList));

	auto& loginToAccount = CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::POST);
	loginToAccount(LoginHandler(userList));

	auto& getMultipleAnswerQuestion = CROW_ROUTE(app, "/getmultiplequestion");
	getMultipleAnswerQuestion(MultipleAnswerQuestionHandler(currentGame));

	auto& getNumericalAnswerQuestion = CROW_ROUTE(app, "/getnumericalquestion");
	getNumericalAnswerQuestion(NumericalAnswerQuestionHandler(currentGame));

	std::unordered_map<uint32_t, Lobby> onGoingLobbies;
	auto& createNewLobby = CROW_ROUTE(app, "/newlobby");
	createNewLobby(CreateLobbyHandler(onGoingLobbies));

	auto& addToLobby = CROW_ROUTE(app, "/addplayertolobby").methods(crow::HTTPMethod::PUT);
	addToLobby(AddToLobbyHandler(onGoingLobbies));

	auto& waitInLobby = CROW_ROUTE(app, "/waitinginlobby");
	waitInLobby(WaitingInLobbyHandler(onGoingLobbies));

	auto& removePlayerFromLobby = CROW_ROUTE(app, "/removeplayerfromlobby");
	removePlayerFromLobby(RemoveFromLobbyHandler(onGoingLobbies));

	auto& sendAnswerForMultipleQuestion = CROW_ROUTE(app, "/sendanswer/multiple");
	sendAnswerForMultipleQuestion(SendAnswerMultipleQuestion(currentGame));

	auto& sendAsnwerForNumericalQuestion = CROW_ROUTE(app, "/sendanswer/numerical");
	sendAsnwerForNumericalQuestion(SendAnswerNumericalQuestion(currentGame));

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

	//auto& createNewGame = CROW_ROUTE(app, "/newgame").methods(crow::HTTPMethod::PUT);
	//createNewGame(CreateGameHandler(game, lobby));

	app.port(18080).multithreaded().run();
	return 0;
}
