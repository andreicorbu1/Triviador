#pragma once
#include <crow.h>
#include "utils.h"
#include "Game.h"
#include <nlohmann/json.hpp>

void to_json(nlohmann::json& json, const Player& player);

class GetAllPlayersFromGameHandler
{
public:
	GetAllPlayersFromGameHandler(Game& game);
	crow::response operator()(const crow::request& req) const;

private:
	Game& m_game;
};