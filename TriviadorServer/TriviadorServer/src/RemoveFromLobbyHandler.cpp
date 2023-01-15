#include "RemoveFromLobbyHandler.h"

RemoveFromLobbyHandler::RemoveFromLobbyHandler(Lobby& lobby, AccountManager& userList): 
	m_lobby(lobby),
	m_userList(userList)
{
}

crow::response RemoveFromLobbyHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto idArg = bodyArgs.find("id");
	auto usernameArg = bodyArgs.find("username");
	
	if (idArg == end || usernameArg == end)
	{
		return crow::response(416, "Lobby ID or/and username isn't/aren't sent properly");
	}
	
	std::string username = usernameArg->second;
	if (!m_userList.SearchUser(username))
	{
		return crow::response(404, "User list doesn't contain inserted username");
	}
	
	int id = std::stoi(idArg->second);
	if (m_lobby.GetLobbyID() != id)
	{
		return crow::response(404, "Lobby not found");
	}
	
	if (m_lobby.RemovePlayer(username))
	{
		if (m_lobby.GetNumberOfPlayers() == 0)
		{
			m_lobby.ClearLobby();
		}
		
		return crow::response(200, "Successfully Removed Player from Lobby");
	}

	return crow::response(400, "Lobby doesn't contain any player with inserted username");
}
