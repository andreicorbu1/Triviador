#include "CreateLobbyHandler.h"

CreateLobbyHandler::CreateLobbyHandler(std::unordered_map<uint32_t, Lobby>& onGoingLobbies):
	m_onGoingLobbies(onGoingLobbies)
{
}

crow::json::wvalue CreateLobbyHandler::operator()(const crow::request& req) const
{
	Lobby lobby;
	m_onGoingLobbies[lobby.GetLobbyID()] = lobby;
	crow::json::wvalue jsonWithLobbyID
	{
		{"lobby_id", lobby.GetLobbyID()}
	};
	
	return crow::json::wvalue(jsonWithLobbyID);
}
