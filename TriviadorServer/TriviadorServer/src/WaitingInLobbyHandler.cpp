#include "WaitingInLobbyHandler.h"

WaitingInLobbyHandler::WaitingInLobbyHandler(Lobby& lobby) : m_lobby(lobby)
{
}

crow::response WaitingInLobbyHandler::operator()(const crow::request& req) const
{
	if (m_lobby.IsActiveGame()) 
	{
		return crow::response(300, "Game Started");
	}
	
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto lobbyIdArg = bodyArgs.find("id");
	
	if (lobbyIdArg == end)
	{
		return crow::response(400, "Lobby ID isn't sent properly");
	}
	
	int lobbyId = std::stoi(lobbyIdArg->second);
	if (m_lobby.GetLobbyID() != lobbyId)
	{
		return crow::response(402, "No lobby which contains inserted id");
	}
	
	if (!m_lobby.HadExpired())
	{
		return crow::response(100, "Waiting");
	}
	else
	{
		m_lobby.ClearLobby();
		return crow::response(410, "Lobby waiting time has expired");
	}
}
