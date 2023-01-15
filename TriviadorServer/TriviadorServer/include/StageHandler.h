#pragma once
#include "Game.h"
#include "AccountsManager.h"

class StageHandler
{
public:
	StageHandler(Game& game, AccountManager& userList);
	crow::response operator()(const crow::request& req) const;
private:
	Game& m_game;
	AccountManager& m_userList;
};