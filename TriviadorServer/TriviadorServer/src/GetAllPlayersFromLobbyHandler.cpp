#include "GetAllPlayersFromLobbyHandler.h"

GetAllPlayersFromLobbyHandler::GetAllPlayersFromLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies) : m_onGoingLobbies(onGoingLobbies)
{
}

crow::json::wvalue GetAllPlayersFromLobbyHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto lobbyID = bodyArgs.find("id");
	if (lobbyID != end)
	{
		auto id = std::stoi(lobbyID->second);
		if (m_onGoingLobbies.contains(id))
		{
			std::vector<Player>players;
			int numberOfPlayersFromLobby = m_onGoingLobbies.at(id).GetNumberOfPlayers();

			for (int i = 0; i < numberOfPlayersFromLobby; i++)
			{
				Player player = m_onGoingLobbies.at(id).GetPlayerAt(i);
				players.push_back(player);
			}

			nlohmann::json json = players;
			std::string jsonString = json.dump();

			return crow::json::wvalue(crow::json::load(jsonString));

		}
		crow::json::wvalue invalidID
		{
			{ "invalid_id", "No lobby which contains inserted id" }
		};
		return crow::json::wvalue(invalidID);
	}
	crow::json::wvalue noID
	{
		{ "invalid_id", "NO ID" }
	};
	return crow::json::wvalue(noID);
}

void to_json(nlohmann::json& json, const Player& player)
{
	json =
	{
		{"name", player.GetName()},
		{"color", player.ColorToString(player.GetColor())}
	};
}