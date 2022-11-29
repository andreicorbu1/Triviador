#pragma once
#include "AccountsManager.h"
#include "utils.h"
#include <crow.h>

struct LoginHandler
{
	LoginHandler(AccountManager& accountList);
	crow::response operator()(const crow::request& req) const;
private:
	AccountManager& m_accountList;
};