#pragma once
#include <crow.h>
#include "AccountsManager.h"
struct AddAccountHandler
{
public:
	AddAccountHandler(AccountManager& accountList);
	crow::response operator()(const crow::request& req) const;
private:
	AccountManager& m_accountList;
};
