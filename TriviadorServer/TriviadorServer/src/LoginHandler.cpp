#include "LoginHandler.h"

LoginHandler::LoginHandler(AccountManager& accountList) : m_accountList(accountList)
{}

crow::response LoginHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	auto passwordIter = bodyArgs.find("password");
	if (usernameIter != end && passwordIter != end)
	{
		if (m_accountList.SearchUser(usernameIter->second) == true)
		{
			if (m_accountList.GetUser(usernameIter->second).GetPassword() == passwordIter->second)
			{
				return crow::response(200, "Autentificare cu succes!");
			}
			else
			{
				return crow::response(401, "Parola introdusa este gresita. Va rugam reincercati!");
			}
		}
		else
		{
			return crow::response(403, "Username-ul introdus nu exista!");
		}
	}
	else
	{
		return crow::response(400);
	}
}
