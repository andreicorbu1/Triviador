#pragma once
#include "Player.h"
#include <vector>
#include <random>
#include <chrono>

class Lobby
{
public:
	Lobby();
	void AddPlayer();
	int GetNumberOfPlayers();
	uint32_t GetLobbyID();
	const std::chrono::system_clock::time_point& GetExpirationTime() const;
private:
	std::vector<int> m_players;
	uint32_t m_lobbyId;
	uint32_t GenerateRandomLobbyID();
	std::chrono::system_clock::time_point m_expirationTime;
};

