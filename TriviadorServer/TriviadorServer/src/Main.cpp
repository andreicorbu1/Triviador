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
#include "SendAnswerMultipleQuestion.h"
#include "SendAnswerNumericalQuestion.h"
#include "QuestionManager.h"
#include "Game.h"

int main()
{
	AccountManager userList("resource/Accounts.sqlite");
	QuestionManager questionManager("resource/Questions.sqlite");
	questionManager.PopulateStorage();
	Game currentGame;
	crow::SimpleApp app;

	auto& addUserToAccountList = CROW_ROUTE(app, "/signup").methods(crow::HTTPMethod::PUT);
	addUserToAccountList(AddAccountHandler(userList));

	auto& loginToAccount = CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::POST);
	loginToAccount(LoginHandler(userList));

	auto& getMultipleAnswerQuestion = CROW_ROUTE(app, "/getmultiplequestion");
	getMultipleAnswerQuestion(MultipleAnswerQuestionHandler(currentGame));

	auto& getNumericalAnswerQuestion = CROW_ROUTE(app, "/getnumericalquestion");
	getNumericalAnswerQuestion(NumericalAnswerQuestionHandler(currentGame));

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

	auto& sendAnswerForMultipleQuestion = CROW_ROUTE(app, "/sendanswer/multiple");
	sendAnswerForMultipleQuestion(SendAnswerMultipleQuestion(currentGame));

	auto& sendAsnwerForNumericalQuestion = CROW_ROUTE(app, "/sendanswer/numerical");
	sendAsnwerForNumericalQuestion(SendAnswerNumericalQuestion(currentGame));

	auto& createNewGame = CROW_ROUTE(app, "/newgame").methods(crow::HTTPMethod::PUT);
	createNewGame(CreateGameHandler(currentGame, lobby));

	app.port(18080).multithreaded().run();
	return 0;
}
