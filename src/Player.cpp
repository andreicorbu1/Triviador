#include "Player.h"

Player::Player(const std::string& playerName, const Color& color) :
	m_playerName(playerName), m_color(color)
{
	m_score = 0;
	m_territoriesCount = 0;
}

Player& Player::operator+=(const int score)
{
	m_score += score;
	return *this;
}
