#pragma once
#include <string>
#include "Territory.h"
#include <vector>
#include <memory>
#include <algorithm>

class Player
{
public:
	enum class Color
	{
		None,
		Blue,
		Red,
		Green,
		Yellow
	};

	static Color ToColor(std::string color);
	static std::string ToString(Color color);

public:
	Player() = default;
	Player(const std::string& playerName, const Color& color);
	Player(const Player& other);
	Player(Player&& other) noexcept;
	~Player() = default;

	// Getters:
	const std::string& GetName() const;
	Player::Color GetColor() const;
	uint16_t GetScore() const;
	uint16_t GetRank() const;
	/*std::vector<std::reference_wrapper<Territory>> GetOwnedTerritories() const;
	std::vector<std::reference_wrapper<Territory>>& GetOwnedTerritories();*/

	// Setters:
	void SetName(const std::string& name);
	void SetColor(const Player::Color& color);
	void SetScore(const uint16_t& score);
	void SetRank(const uint16_t& rank);

	//Other:
	void AddScore(uint16_t score);/*
	void AddTerritory(Territory& territory);
	void RemoveTerritory(Territory& territory);*/

	// Operators:
	Player& operator =(const Player& other);
	Player& operator =(Player&& other) noexcept;
	bool operator <(const Player& other);

private:
	std::string m_playerName;
	Color m_color;
	uint16_t m_score;
	uint16_t m_rank;
	//std::vector<std::reference_wrapper<Territory>> m_ownedTerritories;
};

