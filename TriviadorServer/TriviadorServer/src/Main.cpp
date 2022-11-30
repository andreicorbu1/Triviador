#include "AddToAcountListHandler.h"
#include "LoginHandler.h"
#include <crow.h>

int main()
{
	AccountManager userList;
	crow::SimpleApp app;

	//register route
	auto& addUserToAccountList = CROW_ROUTE(app, "/signup").methods(crow::HTTPMethod::PUT);
	addUserToAccountList(AddAccountHandler(userList));

	//login route
	auto& loginToAccount = CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::POST);
	loginToAccount(LoginHandler(userList));

	app.port(18080).multithreaded().run();
	return 0;
}
