#include "AddToAcountListHandler.h"
#include "utils.h"
AddAccountHandler::AddAccountHandler(AccountManager& accountList) : m_accountList(accountList)
{}

crow::response AddAccountHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	auto passwordIter = bodyArgs.find("password");
	if (usernameIter != end && passwordIter != end)
	{
		if (m_accountList.SearchUser(usernameIter->second) == true)
		{
			return crow::response(403, "Username-ul introdus este deja existent.");
		}
		User userRow(usernameIter->second, passwordIter->second);
		m_accountList.AddUser(userRow);
		if (m_accountList.SearchUser(usernameIter->second) == false)
		{
			return crow::response(403, "Parola nu a putut fi validata, va rugam sa aveti cel putin o litera mare, un caracter special si cel putin o cifra.");
		}
		return crow::response(201, "V-ati inregistrat cu succes");
	}
	else
	{
		return crow::response(400);
	}
}
