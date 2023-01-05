#include "WaitingInLobbyHandler.h"

WaitingInLobbyHandler::WaitingInLobbyHandler(Lobby& lobby) : m_lobby(lobby)
{
}

crow::response WaitingInLobbyHandler::operator()(const crow::request& req) const
{
	if (m_lobby.GetIsActiveGame() == false) {
		auto bodyArgs = ParseUrlArgs(req.body);
		auto end = bodyArgs.end();
		auto lobbyID = bodyArgs.find("id");
		if (lobbyID != end)
		{
			int id = std::stoi(lobbyID->second);
			if (m_lobby.GetLobbyID() == id)
			{
				if (std::chrono::system_clock::to_time_t(m_lobby.GetExpirationTime())
				> std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
				{
					return crow::response(100, "Waiting");
				}
				else
				{
					m_lobby.ClearLobby();
					return crow::response(410, "Lobby waiting time has expired");
				}
			}
			else
			{
				return crow::response(404, "Lobby not found");
			}
		}
		return crow::response(416, "NO ID");
	}
	return crow::response(300, "Game Started");
}
