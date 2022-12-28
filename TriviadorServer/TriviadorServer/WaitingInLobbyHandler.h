#pragma once
#include <crow.h>
#include "utils.h"
#include <Lobby.h>
#include <unordered_map>
class WaitingInLobbyHandler
{
public:
	WaitingInLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies);
	crow::response operator()(const crow::response& req) const;
private:
	std::unordered_map<uint32_t, Lobby>& m_onGoingLobbies;
};

