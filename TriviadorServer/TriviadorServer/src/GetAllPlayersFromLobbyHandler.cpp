#include "GetAllPlayersFromLobbyHandler.h"

GetAllPlayersFromLobbyHandler::GetAllPlayersFromLobbyHandler(Lobby& lobby) : m_lobby(lobby)
{
}

crow::json::wvalue GetAllPlayersFromLobbyHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto lobbyID = bodyArgs.find("id");
	
	if (lobbyID == end)
	{
		crow::json::wvalue noID
		{
			{ "invalid_id", "NO ID" }
		};
		return crow::json::wvalue(noID);
	}

	if (auto id = std::stoi(lobbyID->second); m_lobby.GetLobbyID() != id)
	{
		crow::json::wvalue invalidID
		{
			{ "invalid_id", "No lobby which contains inserted id" }
		};
		return crow::json::wvalue(invalidID);
	}

	std::vector<Player>players;
	int numberOfPlayersFromLobby = m_lobby.GetNumberOfPlayers();

	for (int i = 0; i < numberOfPlayersFromLobby; i++)
	{
		Player player = m_lobby.GetPlayerAt(i);
		players.push_back(player);
	}

	nlohmann::json json = players;
	std::string jsonString = json.dump();

	return crow::json::wvalue(crow::json::load(jsonString));
}