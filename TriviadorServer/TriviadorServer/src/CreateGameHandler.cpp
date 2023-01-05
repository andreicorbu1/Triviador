#include "CreateGameHandler.h"

CreateGameHandler::CreateGameHandler(Game& game, Lobby& lobby) : m_game(game), m_lobby(lobby)
{}

crow::response CreateGameHandler::operator()(const crow::request& req) const
{
	m_game = Game(m_lobby.GetPlayers());
	m_lobby.SetIsActiveGame(true);
	return crow::response(200, "Game created successfully");
}
