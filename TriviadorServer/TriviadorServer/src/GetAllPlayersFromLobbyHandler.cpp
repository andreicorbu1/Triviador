#include "GetAllPlayersFromLobbyHandler.h"

GetAllPlayersFromLobbyHandler::GetAllPlayersFromLobbyHandler(Lobby& lobby) : m_lobby(lobby)
{
}

crow::response GetAllPlayersFromLobbyHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto lobbyIdArg = bodyArgs.find("id");
	
	if (lobbyIdArg == end)
	{
		return crow::response(400, "Lobby ID isn't sent properly");
	}

	if (auto id = std::stoi(lobbyIdArg->second); m_lobby.GetLobbyID() != id)
	{
		return crow::response(402, "No lobby which contains inserted id");
	}

	std::vector<Player>players;
	int lobbyPlayerCount = m_lobby.GetNumberOfPlayers();

	if (lobbyPlayerCount == 0)
	{
		m_lobby.ClearLobby();
		return crow::response(404, "Lobby is empty");
	}
	
	for (int i = 0; i < lobbyPlayerCount; i++)
	{
		Player player = m_lobby.GetPlayerAt(i);
		players.push_back(player);
	}

	nlohmann::json json = players;
	std::string jsonString = json.dump();

	return crow::json::wvalue(crow::json::load(jsonString));
}