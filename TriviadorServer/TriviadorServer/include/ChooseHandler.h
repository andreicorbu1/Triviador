#pragma once
#include "Game.h"

class ChooseHandler
{
public:
	ChooseHandler(Game& game);
	crow::response operator()(const crow::request& req) const;
private:
	Game& m_game;
};

