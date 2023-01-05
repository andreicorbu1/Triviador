#include "CreateGameHandler.h"

CreateGameHandler::CreateGameHandler(Game& game, Lobby& lobby) : m_game(game), m_lobby(lobby)
{}

crow::response CreateGameHandler::operator()(const crow::request& req) const
{
	try
	{
		m_game = Game(m_lobby.GetPlayers());
		if (m_game.GetPlayers() != m_lobby.GetPlayers())
		{
			return crow::response(400, "Game wasn't created succesfully");
		}
		return crow::response(200, "Game created successfully");
	}
	catch(const std::exception& e)
	{
		return crow::response(400, e.what());
	}
}
