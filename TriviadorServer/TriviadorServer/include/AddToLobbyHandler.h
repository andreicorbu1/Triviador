#pragma once
#include "crow.h"
#include "AccountsManager.h"
#include "Lobby.h"
#include "utils.h"
#include <random>

struct AddToLobbyHandler
{
	AddToLobbyHandler(Lobby& lobby, AccountManager& acountList);
	crow::response operator()(const crow::request& req) const;

private:
	Lobby& m_lobby;
	AccountManager& m_userList;
};

