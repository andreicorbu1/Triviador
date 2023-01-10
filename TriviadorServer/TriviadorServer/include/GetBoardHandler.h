#pragma once
#include "utils.h"
#include <crow.h>
#include "Game.h"

class GetBoardHandler
{
public:
	GetBoardHandler(Game& game);
	crow::response operator()(const crow::request& req) const;

private:
	Game& m_game;
};

