#include "CreateLobbyHandler.h"

CreateLobbyHandler::CreateLobbyHandler(std::unordered_map<uint32_t, Lobby> onGoingLobbies):
	m_onGoingLobbies(onGoingLobbies)
{
}

crow::response CreateLobbyHandler::operator()(const crow::request& req) const
{
	//Lobby lobby;
	//m_onGoingLobbies[lobby.GetLobbyID()] = lobby;
	
	//Problema e ca nu putem modifica m_onGoingLobbies chiar daca e referinta 

	return crow::response(200, "Good one");
}
