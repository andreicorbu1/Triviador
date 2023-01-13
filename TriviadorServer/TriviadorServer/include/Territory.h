#pragma once
#include "Player.h"
#include <memory>
#include <iostream>
#include <optional>

class Territory
{
public:
	//Constructors
	Territory();
	Territory(const std::optional<Player>& owner, const bool& isBase);
	Territory(const Player& owner, const bool& isBase);
	Territory(const Territory& territory);
	Territory(Territory&& territory) noexcept;
	~Territory() = default;

	//Getters:
	std::optional<Player> GetOwner() const;
	uint16_t GetScore() const;

	//Setters:
	void SetOwner(const std::optional<Player>& owner);
	void SetScore(const uint16_t& score);
	void AddScore(const uint16_t& score);
	void RemoveScore(const uint16_t& score);
	// Operators:
	Territory& operator=(const Territory& territory);
	Territory& operator=(Territory&& territory) noexcept;
	bool operator==(const Territory& other) const;

	friend std::ostream& operator<< (std::ostream& out, const Territory& t);

private:
	const uint16_t kBaseScore = 300;
	const uint16_t kTerritoryScore = 100;

private:
	std::optional<Player> m_owner;
	uint16_t m_score;
	bool m_isBase;
};

