#pragma once
#include <crow.h>
#include "utils.h"
#include "Lobby.h"
#include <nlohmann/json.hpp>

void to_json(nlohmann::json& json, const Player& player);

class GetAllPlayersFromLobbyHandler
{
public:
	GetAllPlayersFromLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies);
	crow::json::wvalue operator()(const crow::request& req) const;


private:
	std::unordered_map<uint32_t, Lobby>& m_onGoingLobbies;
};