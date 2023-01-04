#pragma once
#include "Player.h"
#include <vector>
#include <array>
#include <random>
#include <chrono>

class Lobby
{
public:
	Lobby();
	Lobby(const Player& player);

	void AddPlayer(const Player& player);
	bool RemovePlayer(const std::string& username);

	const Player& GetPlayerAt(int index) const;
	int GetNumberOfPlayers();
	uint32_t GetLobbyID();
	const std::chrono::system_clock::time_point& GetExpirationTime() const;

private:
	void SetAvailableColors();

	std::vector<Player> m_players;
	uint32_t m_lobbyId;
	uint32_t GenerateRandomLobbyID();
	std::chrono::system_clock::time_point m_expirationTime;
	static const size_t kNumberOfColors = 4;
	std::vector<int>m_availableColors;
};

