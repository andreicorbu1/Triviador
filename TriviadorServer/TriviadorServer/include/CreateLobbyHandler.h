#pragma once
#include "crow.h"
#include "Lobby.h"
#include "AccountsManager.h"
#include "utils.h"
#include <random>

class CreateLobbyHandler
{
public:
	CreateLobbyHandler() = delete;
	CreateLobbyHandler(Lobby& lobby, AccountManager& userList);
	crow::response operator()(const crow::request& req) const;

private:
	AccountManager& m_userList;
	Lobby& m_lobby;
};

