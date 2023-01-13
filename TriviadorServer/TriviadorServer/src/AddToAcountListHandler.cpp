#include "AddToAcountListHandler.h"

AddAccountHandler::AddAccountHandler(AccountManager& accountList) : m_accountList(accountList)
{}

crow::response AddAccountHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	auto passwordIter = bodyArgs.find("password");
	
	if (usernameIter == end || passwordIter == end)
	{
		return crow::response(400);
	}
	
	if (m_accountList.SearchUser(usernameIter->second))
	{
		return crow::response(403, "Username already exists");
	}
	
	User userRow(usernameIter->second, passwordIter->second);
	m_accountList.AddUser(userRow);
	
	if (!m_accountList.SearchUser(usernameIter->second))
	{
		return crow::response(403, "Password is invalid.Please try again");
	}
	
	return crow::response(201, "Successfully Added User");
}
