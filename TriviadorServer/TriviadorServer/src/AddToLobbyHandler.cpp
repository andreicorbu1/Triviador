#include "AddToLobbyHandler.h"

AddToLobbyHandler::AddToLobbyHandler(Lobby& lobby, AccountManager& userList) :
	m_lobby(lobby),
	m_userList(userList)
{}

crow::response AddToLobbyHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto lobbyID = bodyArgs.find("id");
	auto userName = bodyArgs.find("username");
	if (lobbyID != end && userName != end)
	{
		std::string username = userName->second;
		if (m_userList.SearchUser(username))
		{
			auto id = std::stoi(lobbyID->second);
			if (m_lobby.GetLobbyID() == id)
			{
				int numberOfPlayersFromLobby = m_lobby.GetNumberOfPlayers();
				if (numberOfPlayersFromLobby < 4)
				{
					Player playerToBeInserted(username, Player::Color::None);
					if (auto result = std::ranges::find_if(m_lobby.GetPlayers(),
						[&playerToBeInserted](const Player& player) { return player.GetName() == playerToBeInserted.GetName(); }); result != m_lobby.GetPlayers().end())
						return crow::response(404, "User already in lobby");
					m_lobby.AddPlayer(Player(username, Player::Color::None));
					return crow::response(200, "Successfully Added Player to Lobby");
				}
				return crow::response(401, "Full lobby");
			}
			return crow::response(402, "No lobby which contains inserted id");
		}
		return crow::response(403, "User list doesn't contain inserted username");
	}
	return crow::response(400, "Lobby ID or/and username isn't/aren't sent properly");
}
