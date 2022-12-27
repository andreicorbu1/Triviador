#include "AddToLobbyHandler.h"

AddToLobbyHandler::AddToLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies) : m_onGoingLobbies(onGoingLobbies)
{}

crow::response AddToLobbyHandler::operator()(const crow::request & req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto lobbyID = bodyArgs.find("id");
	if (lobbyID != end)
	{
		auto id = std::stoi(lobbyID->second);
		if (m_onGoingLobbies.contains(id))
		{
			if (m_onGoingLobbies.at(id).GetNumberOfPlayers() < 4)
			{
				m_onGoingLobbies.at(id).AddPlayer();
				return crow::response(200, "Successfully Added Player to Lobby");
			}
			return crow::response(401, "Full lobby");
		}
	}
	return crow::response(400, "Lobby not found");
}
