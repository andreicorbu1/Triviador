#pragma once
#include "Player.h"
#include <vector>
#include <random>

class Lobby
{
public:
	Lobby();
	void AddPlayer();
	uint32_t GetLobbyID();

private:
	std::vector<int> m_players;
	uint32_t m_lobbyId;
	uint32_t GenerateRandomLobbyID();
};

