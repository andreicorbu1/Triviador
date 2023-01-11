#pragma once
#include "crow.h"
#include "PlayerHistoryManager.h"
#include "utils.h"

class AddToPlayerHistoryHandler
{
public:
	AddToPlayerHistoryHandler(PlayerHistoryManager& playerHistoryManager);
	crow::response operator()(const crow::request& req) const;
private:
	PlayerHistoryManager& m_playerHistoryManager;
};

