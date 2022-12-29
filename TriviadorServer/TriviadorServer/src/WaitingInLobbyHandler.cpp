#include "WaitingInLobbyHandler.h"

WaitingInLobbyHandler::WaitingInLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies): m_onGoingLobbies(onGoingLobbies)
{
}

crow::response WaitingInLobbyHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto lobbyID = bodyArgs.find("id");
	if (lobbyID != end)
	{
		int id = std::stoi(lobbyID->second);
		if (m_onGoingLobbies.contains(id))
		{
			if (std::chrono::system_clock::to_time_t(m_onGoingLobbies.at(id).GetExpirationTime()) 
				> std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
			{
				return crow::response(100, "Waiting");
			}
			else
			{
				m_onGoingLobbies.erase(id);
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
