#include "Lobby.h"

Lobby::Lobby()
{
	m_lobbyId = GetLobbyID();
}

void Lobby::AddPlayer()
{
	m_players.push_back(1);
}

uint32_t Lobby::GenerateRandomLobbyID()
{
	std::random_device rd;
	std::uniform_int_distribution<int> dist(1000, 9999);

	return dist(rd);
}

uint32_t Lobby::GetLobbyID()
{
	return m_lobbyId;
}
