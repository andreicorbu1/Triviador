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
	auto lobbyID = bodyArgs.find("id");
	auto userName = bodyArgs.find("username");
	if (lobbyID != end && userName!=end)
	{
		std::string username = userName->second;
		if (m_userList.SearchUser(username))
		{
			int id = std::stoi(lobbyID->second);
			if (m_lobby.GetLobbyID()==id)
			{
				if (m_lobby.RemovePlayer(username))
				{
					return crow::response(200, "Successfully Removed Player from Lobby");
				}
				return crow::response(400, "Lobby doesn't contain any player with inserted username");
			}
			return crow::response(404, "Lobby not found");
		}
		return crow::response(404, "User list doesn't contain inserted username");
	}
	return crow::response(416, "Lobby ID or/and username isn't/aren't sent properly");
}
