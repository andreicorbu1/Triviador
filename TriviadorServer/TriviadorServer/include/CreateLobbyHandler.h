#pragma once
#include "crow.h"
#include "Lobby.h"
#include "utils.h"
#include <random>

class CreateLobbyHandler
{
public:
	CreateLobbyHandler() = delete;
	CreateLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies);
	crow::json::wvalue operator()(const crow::request& req) const;
private:
	//	std::unordered_map<uint32_t, Lobby> m_onGoingLobbies;
	std::unordered_map<uint32_t, Lobby>& m_onGoingLobbies;
};

