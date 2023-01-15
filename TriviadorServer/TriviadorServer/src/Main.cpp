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
#include "GetAllPlayersFromGameHandler.h"
#include "MultipleAnswerQuestion.h"
#include "SendAnswerMultipleQuestion.h"
#include "SendAnswerNumericalQuestion.h"
#include "StageHandler.h"
#include "GetBoardHandler.h"
#include "QuestionManager.h"
#include "PlayerHistoryHandler.h"
#include "AddToPlayerHistoryHandler.h"
#include "ChooseHandler.h"
#include "AttackTerritoryHandler.h"
#include "GetUserStatsHandler.h"

int main()
{
	AccountManager userList("resource/Accounts.sqlite");
	QuestionManager questionManager("resource/Questions.sqlite");
	PlayerHistoryManager playerHistoryManager("resource/PlayersHistory.sqlite");
	questionManager.PopulateStorage();
	Game currentGame;

	Lobby lobby;

	crow::SimpleApp app;
	app.bindaddr("25.65.182.120");

	auto& addUserToAccountList = CROW_ROUTE(app, "/signup").methods(crow::HTTPMethod::PUT);
	addUserToAccountList(AddAccountHandler(userList));

	auto& loginToAccount = CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::POST);
	loginToAccount(LoginHandler(userList));

	auto& getMultipleAnswerQuestion = CROW_ROUTE(app, "/question/multiple");
	getMultipleAnswerQuestion(MultipleAnswerQuestionHandler(currentGame));

	auto& getNumericalAnswerQuestion = CROW_ROUTE(app, "/question/numerical");
	getNumericalAnswerQuestion(NumericalAnswerQuestionHandler(currentGame));

	auto& sendAnswerForMultipleQuestion = CROW_ROUTE(app, "/sendanswer/multiple");
	sendAnswerForMultipleQuestion(SendAnswerMultipleQuestion(currentGame));

	auto& sendAsnwerForNumericalQuestion = CROW_ROUTE(app, "/sendanswer/numerical");
	sendAsnwerForNumericalQuestion(SendAnswerNumericalQuestion(currentGame));

	auto& createNewLobby = CROW_ROUTE(app, "/newlobby");
	createNewLobby(CreateLobbyHandler(lobby, userList));

	auto& addToLobby = CROW_ROUTE(app, "/lobby/addplayer").methods(crow::HTTPMethod::PUT);
	addToLobby(AddToLobbyHandler(lobby, userList));

	auto& waitInLobby = CROW_ROUTE(app, "/lobby/waiting");
	waitInLobby(WaitingInLobbyHandler(lobby));

	auto& removePlayerFromLobby = CROW_ROUTE(app, "/lobby/removeplayer");
	removePlayerFromLobby(RemoveFromLobbyHandler(lobby, userList));

	auto& getPlayersFromLobby = CROW_ROUTE(app, "/lobby/players");
	getPlayersFromLobby(GetAllPlayersFromLobbyHandler(lobby));
	
	auto& createNewGame = CROW_ROUTE(app, "/lobby/creategame").methods(crow::HTTPMethod::PUT);
	createNewGame(CreateGameHandler(currentGame, lobby));

	auto& stage = CROW_ROUTE(app, "/game/stage");
	stage(StageHandler(currentGame, userList));

	auto& getBoard = CROW_ROUTE(app, "/game/board");
	getBoard(GetBoardHandler(currentGame));

	auto& getPlayersFromGame = CROW_ROUTE(app, "/game/players");
	getPlayersFromGame(GetAllPlayersFromGameHandler(currentGame));

	auto& sendPlayerHistory = CROW_ROUTE(app, "/playerhistory");
	sendPlayerHistory(PlayerHistoryHandler(playerHistoryManager));

	auto& addPlayerHistory = CROW_ROUTE(app, "/addplayerhistory").methods(crow::HTTPMethod::PUT);
	addPlayerHistory(AddToPlayerHistoryHandler(playerHistoryManager));

	auto& chooseBase = CROW_ROUTE(app, "/game/choose").methods(crow::HTTPMethod::PUT);
	chooseBase(ChooseHandler(currentGame));

	auto& attack = CROW_ROUTE(app, "/attack");
	attack(AttackTerritoryHanndler(currentGame));

	auto&getPlayerLevelForStats = CROW_ROUTE(app, "/getuserstats");
	getPlayerLevelForStats(GetUserStatsHandler(userList));

	app.port(18080).multithreaded().run();
	return 0;
}
