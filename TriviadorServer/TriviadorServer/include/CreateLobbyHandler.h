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
	CreateLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies, AccountManager& userList);
	crow::json::wvalue operator()(const crow::request& req) const;

private:
	AccountManager& m_userList;
	std::unordered_map<uint32_t, Lobby>& m_onGoingLobbies;
};

