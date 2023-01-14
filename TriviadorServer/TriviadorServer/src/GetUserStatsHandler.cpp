#include "GetUserStatsHandler.h"

GetUserStatsHandler::GetUserStatsHandler(AccountManager& accountList) : m_accountList(accountList)
{
}

crow::response GetUserStatsHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto username = bodyArgs.find("username");
	if (username == end)
	{
		crow::json::wvalue noUsername
		{
			{"invalid_username", "No username"}
		};
		return crow::json::wvalue(noUsername);
	}
	User searchedUser = m_accountList.GetUser(username->second);
	if (searchedUser.GetUsername() == "")
	{
		return crow::json::wvalue
		{
			{"invalid username", "the account doesn't exist"}
		};
	}
	crow::json::wvalue level
	{
		{"level", std::to_string(searchedUser.GetLevel())},
		{"points", std::to_string(searchedUser.GetPoints())}
	};
	return level;
}
