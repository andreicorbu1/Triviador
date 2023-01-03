#include "CreateLobbyHandler.h"

CreateLobbyHandler::CreateLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies, AccountManager& userList):
	m_onGoingLobbies(onGoingLobbies),
	m_userList(userList)
{
}

crow::json::wvalue CreateLobbyHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto userName = bodyArgs.find("username");
	if (userName != end)
	{
		std::string username=userName->second;
		if(m_userList.SearchUser(username))
		{
			Player player(username, Player::Color::Red);
			Lobby lobby(player);
			m_onGoingLobbies[lobby.GetLobbyID()] = lobby;
			crow::json::wvalue jsonWithLobbyID
			{
				{"lobby_id", lobby.GetLobbyID()}
			};
			return crow::json::wvalue(jsonWithLobbyID);
		}
		else
		{
			crow::json::wvalue jsonWithInvalidUsername
			{
				{"invalid_username", "404"}
			};
			return crow::json::wvalue(jsonWithInvalidUsername);
		}
	}

	crow::json::wvalue jsonWithResponse
	{
		{"No Username", "404"}
	};
	return crow::json::wvalue(jsonWithResponse);
}
