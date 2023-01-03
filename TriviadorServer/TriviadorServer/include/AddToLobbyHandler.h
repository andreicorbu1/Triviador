#pragma once
#include "crow.h"
#include "AccountsManager.h"
#include "Lobby.h"
#include "utils.h"
#include <random>

struct AddToLobbyHandler
{
	AddToLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies, AccountManager& acountList);
	crow::response operator()(const crow::request& req) const;

private:
	std::unordered_map<uint32_t, Lobby>& m_onGoingLobbies;
	AccountManager& m_userList;
};

