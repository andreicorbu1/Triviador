#pragma once
#include "Game.h"

class StageHandler
{
public:
	StageHandler(Game& game);
	crow::response operator()(const crow::request& req) const;
private:
	Game& m_game;
};