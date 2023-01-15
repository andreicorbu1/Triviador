#pragma once
#include "AccountsManager.h"
#include <crow.h>
#include "utils.h"
struct GetUserStatsHandler
{
	GetUserStatsHandler(AccountManager& accountList);
	crow::response operator()(const crow::request& req) const;
private:
	AccountManager& m_accountList;
};