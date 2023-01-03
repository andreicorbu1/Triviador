#include "AddToLobbyHandler.h"

AddToLobbyHandler::AddToLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies, AccountManager& userList) :
	m_onGoingLobbies(onGoingLobbies),
	m_userList(userList)
{}

crow::response AddToLobbyHandler::operator()(const crow::request & req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto lobbyID = bodyArgs.find("id");
	auto userName = bodyArgs.find("username");
	if (lobbyID != end)
	{
		if (userName != end)
		{
			std::string username = userName->second;
			if (m_userList.SearchUser(username))
			{
				auto id = std::stoi(lobbyID->second);
				if (m_onGoingLobbies.contains(id))
				{
					int numberOfPlayersFromLobby = m_onGoingLobbies.at(id).GetNumberOfPlayers();
					if (numberOfPlayersFromLobby < 4)
					{
						Player player;
						switch (numberOfPlayersFromLobby)
						{
							case 1:
								player = Player(username, Player::Color::Yellow);
								break;
							case 2:
								player = Player(username, Player::Color::Blue);
							case 3:
								player = Player(username, Player::Color::Green);
						}
						m_onGoingLobbies.at(id).AddPlayer(player);
						return crow::response(200, "Successfully Added Player to Lobby");
					}
					return crow::response(401, "Full lobby");
				}
				return crow::response(404, "User list doesn't contain inserted username");
			}
		}
		return crow::response(400, "No Username");
	}
	return crow::response(400, "Lobby not found");
}
