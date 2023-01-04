#include "CreateLobbyHandler.h"

CreateLobbyHandler::CreateLobbyHandler(Lobby& lobby, AccountManager& userList) :
	m_lobby(lobby),
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
		std::string username = userName->second;
		if (m_userList.SearchUser(username))
		{
			if (m_lobby.GetLobbyID() == INT_MAX)
			{
				Lobby lobby(Player(username, Player::Color::NaN));
				m_lobby = lobby;
				crow::json::wvalue jsonWithLobbyID
				{
					{"lobby_id", lobby.GetLobbyID()}
				};
				return crow::json::wvalue(jsonWithLobbyID);
			}
			return crow::json::wvalue
			{
				{"lobby is already active", "400"}
			};
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
		{"no_username", "404"}
	};
	return crow::json::wvalue(jsonWithResponse);
}
