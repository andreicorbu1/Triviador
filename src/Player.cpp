#include "Player.h"

Player::Player(const std::string& playerName, const Color& color) :
	m_playerName(playerName), m_color(color)
{
	m_score = 0;
	m_territoriesCount = 0;
}

Player::Player(const Player& other)
{
	this->m_score = other.m_score;
	this->m_territoriesCount = other.m_territoriesCount;
	this->m_color = other.m_color;
	this->m_playerName = other.m_playerName;
}

const std::string& Player::GetPlayerName() const
{
	return m_playerName;
}

Player& Player::operator=(const Player& other)
{
	if(this == &other)
	{
		return *this;
	}
	this->m_score = other.m_score;
	this->m_territoriesCount = other.m_territoriesCount;
	this->m_color = other.m_color;
	this->m_playerName = other.m_playerName;
	return *this;
}

Player& Player::operator+=(int score)
{
	m_score += score;
	return *this;
}
