#include "Lobby.h"

Lobby::Lobby()
{
	m_lobbyId = GenerateRandomLobbyID();
	std::chrono::duration<int, std::ratio<1*60>>threeMinutes(1);
	m_expirationTime = std::chrono::system_clock::now() + threeMinutes;
}

void Lobby::AddPlayer()
{
	m_players.push_back(1);
	std::chrono::duration<int, std::ratio<60>>oneMinute(1);
	m_expirationTime += oneMinute;
}

int Lobby::GetNumberOfPlayers()
{
	return m_players.size();
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

const std::chrono::system_clock::time_point& Lobby::GetExpirationTime() const
{
	return m_expirationTime;
}

