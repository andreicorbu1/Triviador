#include "RemoveFromLobbyHandler.h"

RemoveFromLobbyHandler::RemoveFromLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies): m_onGoingLobbies(onGoingLobbies)
{
}

crow::response RemoveFromLobbyHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto lobbyID = bodyArgs.find("id");
	//player id from database=bodyArgs.find("playerID");
	if (lobbyID != end)
	{
		int id = std::stoi(lobbyID->second);
		if (m_onGoingLobbies.contains(id))
		{
			//m_onGoingLobbies[id].RemovePlayer(playerID); 
			m_onGoingLobbies[id].RemovePlayer();
			return crow::response(200, "Successfully Removed Player from Lobby");
		}
		else
		{
			return crow::response(400, "Lobby not found");
		}
	}
	return crow::response(416, "NO ID");
}
