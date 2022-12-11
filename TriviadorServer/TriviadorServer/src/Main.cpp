#include "AddToAcountListHandler.h"
#include "LoginHandler.h"
#include "MultipleAnswerQuestion.h"
#include "QuestionManager.h"
#include "CreateGameHandler.h"
#include "GetPrecisionQuestionHandler.h"
#include "GetMultipleChoiceQuestionHandler.h"
#include "Game.h"
#include <crow.h>

int main()
{
	QuestionManager questionManager("resource/Questions.sqlite");
	questionManager.PopulateStorage();

	AccountManager userList("resource/Accounts.sqlite");
	crow::SimpleApp app;
	std::unordered_map<int32_t, Game> ongoingGames;
	//auto& createNewGame = CROW_ROUTE(app, "/newgame/<int>").methods(crow::HTTPMethod::PUT);
	//createNewGame(CreateGameHandler(ongoingGames));

	auto& addUserToAccountList = CROW_ROUTE(app, "/signup").methods(crow::HTTPMethod::PUT);
	addUserToAccountList(AddAccountHandler(userList));

	auto& loginToAccount = CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::POST);
	loginToAccount(LoginHandler(userList));
	auto& getPrecisionQuestion = CROW_ROUTE(app, "/MultipleAnswerQuestion");
	getPrecisionQuestion(GetPrecisionQuestionHandler(questionManager));

	auto& getMultipleChoiceQuestion = CROW_ROUTE(app, "/NumericalAnswerQuestion");
	getMultipleChoiceQuestion(GetMultipleChoiceQuestionHandler(questionManager));

	app.port(18080).multithreaded().run();
	return 0;
}
