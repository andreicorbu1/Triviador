#pragma once
#include "crow.h"
#include "Lobby.h"
#include "utils.h"
#include <random>

class CreateLobbyHandler
{
private:
	std::unordered_map<uint32_t, Lobby> m_onGoingLobbies;
	//std::unordered_map<uint32_t, Lobby>& m_onGoingLobbies;
public:
	CreateLobbyHandler() = delete;
	CreateLobbyHandler(std::unordered_map<uint32_t, Lobby> onGoingLobbies);
	crow::response operator()(const crow::request& req) const;
};

