#pragma once
#include <crow.h>
#include "utils.h"
#include "Game.h"
#include <nlohmann/json.hpp>

class GetAllPlayersFromGameHandler
{
public:
	GetAllPlayersFromGameHandler(Game& game);
	crow::response operator()(const crow::request& req) const;

private:
	Game& m_game;
};