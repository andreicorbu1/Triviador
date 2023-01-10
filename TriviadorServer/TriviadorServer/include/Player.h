#pragma once
#include <string>

class Player
{
public:
	enum class Color
	{
		Blue,
		Red,
		Green,
		Yellow,
		None
	};

	std::string ColorToString(Color color) const;

public:
	Player() = default;
	Player(const std::string& playerName, const Color& color);
	Player(const Player& other);
	Player(Player&& other) noexcept;
	~Player() = default;

	// Getters:
	const std::string& GetName() const;
	Player::Color GetColor() const;
	size_t GetScore() const;
	int GetTerritoriesCount() const;

	// Setters:
	void SetName(const std::string& name);
	void SetColor(const Player::Color& color);
	void SetScore(const size_t& score);
	void SetTerritoriesCount(const int& territoriesCount);

	//Other:
	void AddScore(size_t score);

	// Operators:
	Player& operator =(const Player& other);
	Player& operator =(Player&& other) noexcept;
	bool operator <(const Player& other);

private:
	std::string m_playerName;
	Color m_color;
	size_t m_score;
	int m_territoriesCount;
};

