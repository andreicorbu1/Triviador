#include "AddToLobbyHandler.h"

AddToLobbyHandler::AddToLobbyHandler(Lobby& lobby, AccountManager& userList) :
	m_lobby(lobby),
	m_userList(userList)
{}

crow::response AddToLobbyHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto lobbyIdArg = bodyArgs.find("id");
	auto usernameArg = bodyArgs.find("username");
	
	if (lobbyIdArg == end || usernameArg == end)
	{
		return crow::response(400, "Lobby ID or/and username isn't/aren't sent properly");
	}
	
	std::string username = usernameArg->second;
	auto lobbyId = std::stoi(lobbyIdArg->second);

	if (!m_userList.SearchUser(username))
	{
		return crow::response(403, "User list doesn't contain inserted username");
	}
	
	if (m_lobby.GetLobbyID() != lobbyId)
	{
		return crow::response(402, "No lobby which contains inserted id");
	}

	int lobbyPlayerCount = m_lobby.GetNumberOfPlayers();
	
	if (lobbyPlayerCount >= 4)
	{
		return crow::response(401, "Full lobby");
	}
	
	Player newPlayer(username, Player::Color::None);
	if (m_lobby.IsInLobby(username))
	{
		return crow::response(404, "User already in lobby");
	}
	
	m_lobby.AddPlayer(Player(username, Player::Color::None));
	
	return crow::response(200, "Successfully Added Player to Lobby");
}
