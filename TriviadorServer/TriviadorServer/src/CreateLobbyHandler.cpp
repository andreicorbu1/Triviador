#include "CreateLobbyHandler.h"

CreateLobbyHandler::CreateLobbyHandler(Lobby& lobby, AccountManager& userList) :
	m_lobby(lobby),
	m_userList(userList)
{
}

crow::response CreateLobbyHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameArg = bodyArgs.find("username");
	if (usernameArg == end)
	{
		return crow::response(404, "Username is invalid");
	}
	
	if (m_lobby.HadExpired())
	{
		m_lobby.ClearLobby();
	}
	
	std::string username = usernameArg->second;
	if (!m_userList.SearchUser(username))
	{
		return crow::response(404, "Username is invalid");
	}
		
	if (m_lobby.GetLobbyID() != INT_MAX)
	{
		return crow::response(402, "Lobby is already created");
	}
	
	Lobby lobby(Player(username, Player::Color::None));
	m_lobby = lobby;
	crow::json::wvalue jsonWithLobbyID
	{
		{"lobby_id", lobby.GetLobbyID()}
	};

	return crow::json::wvalue(jsonWithLobbyID);
}
