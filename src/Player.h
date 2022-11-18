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
		Yellow
	};
	Player() = default;
	Player(const std::string& playerName, const Color& color);
	Player(const Player& other);
	~Player() = default;
	Player& operator =(const Player& other);
	Player& operator+=(int score);

private:
	std::string m_playerName;
	Color m_color;
	size_t m_score;
	int m_territoriesCount;
};

