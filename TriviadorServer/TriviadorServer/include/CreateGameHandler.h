#include <unordered_map>
#include "Game.h"
#include "Lobby.h"
#include <crow.h>
#include "utils.h"
struct CreateGameHandler
{
public:
	CreateGameHandler() = delete;
	CreateGameHandler(Game& game, Lobby& lobby);
	crow::response operator()(const crow::request& req) const;
private:
	Lobby& m_lobby;
	Game& m_game;
};