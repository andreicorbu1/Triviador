#pragma once
#include "PlayerHistoryManager.h"
#include "crow.h"
#include "utils.h"
#include <nlohmann/json.hpp>

class PlayerHistoryHandler
{
public:
	PlayerHistoryHandler(PlayerHistoryManager& playerHistoryManager);
	crow::response operator()(const crow::request& req) const;
private:
	PlayerHistoryManager& m_playerHistoryManager;
};

