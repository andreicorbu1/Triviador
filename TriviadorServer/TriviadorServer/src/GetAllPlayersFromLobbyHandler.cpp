#include "GetAllPlayersFromLobbyHandler.h"

GetAllPlayersFromLobbyHandler::GetAllPlayersFromLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies) : m_onGoingLobbies(onGoingLobbies)
{
}

crow::json::wvalue GetAllPlayersFromLobbyHandler::operator()(const crow::request& req) const
{
	//TODO: Make a vector which return every player details

	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto lobbyID = bodyArgs.find("id");
	if (lobbyID != end)
	{
		auto id = std::stoi(lobbyID->second);
		if (m_onGoingLobbies.contains(id))
		{
			/*int numberOfPlayersFromLobby = m_onGoingLobbies.at(id).GetNumberOfPlayers();
			std::vector<crow::json::wvalue> playersNameFromLobby;
			std::vector<crow::json::wvalue> playersColorFromLobby;
			for (size_t i = 0; i < numberOfPlayersFromLobby; i++)
			{
				Player player = m_onGoingLobbies.at(id).GetPlayerAt(i);
				playersNameFromLobby.push_back(crow::json::wvalue(player.GetName()));
				playersColorFromLobby.push_back(crow::json::wvalue(player.ColorToString(player.GetColor())));
			}
			
			crow::json::wvalue playersDetailsFromLobby
			{
				{"name", playersNameFromLobby},
				{"color", playersColorFromLobby}
			};

			return crow::json::wvalue(playersDetailsFromLobby);*/
			
			std::vector<Player>players;
			int numberOfPlayersFromLobby = m_onGoingLobbies.at(id).GetNumberOfPlayers();
			for (int i = 0; i < numberOfPlayersFromLobby; i++)
			{
				Player player = m_onGoingLobbies.at(id).GetPlayerAt(i);
				players.push_back(player);
			}

			nlohmann::json json = players;
			std::string jsonString = json.dump();


			//std::cout << std::setw(2) << json << std::endl;


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
