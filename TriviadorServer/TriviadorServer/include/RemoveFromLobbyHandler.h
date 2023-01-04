#pragma once
#include <AccountsManager.h>
#include <Lobby.h>
#include "crow.h"
#include "utils.h"

class RemoveFromLobbyHandler
{
public:
	RemoveFromLobbyHandler() = default;
	RemoveFromLobbyHandler(Lobby& lobby, AccountManager& userList);
	crow::response operator()(const crow::request& req) const;
private:
	Lobby& m_lobby;
	AccountManager& m_userList;
};

