#pragma once
#include <crow.h>
#include "utils.h"
#include <Lobby.h>

class WaitingInLobbyHandler
{
public:
	WaitingInLobbyHandler(Lobby& lobby);
	crow::response operator()(const crow::request& req) const;

private:
	Lobby& m_lobby;
};

