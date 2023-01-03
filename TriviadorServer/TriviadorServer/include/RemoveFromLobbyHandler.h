#pragma once
#include <AccountsManager.h>
#include <Lobby.h>
#include "crow.h"
#include "utils.h"

class RemoveFromLobbyHandler
{
public:
	RemoveFromLobbyHandler() = default;
	RemoveFromLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies, AccountManager& userList);
	crow::response operator()(const crow::request& req) const;
private:
	std::unordered_map<uint32_t, Lobby>& m_onGoingLobbies;
	AccountManager& m_userList;
};

