#include "Player.h"

std::string Player::ColorToString(Player::Color color) const
{
	switch (color)
	{
	case Player::Color::Blue:
		return "Blue";
		break;
	case Player::Color::Red:
		return "Red";
		break;
	case Player::Color::Green:
		return "Green";
		break;
	case Player::Color::Yellow:
		return "Yellow";
		break;
	case Player::Color::NaN:
		return "Nan";
		break;
	default:
		break;
	}
}

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

Player::Player(Player&& other) noexcept
{
	*this = std::move(other);
}

const std::string& Player::GetName() const
{
	return m_playerName;
}

Player::Color Player::GetColor() const
{
	return m_color;
}

size_t Player::GetScore() const
{
	return m_score;
}

int Player::GetTerritoriesCount() const
{
	return m_territoriesCount;
}

void Player::SetName(const std::string& name)
{
	this->m_playerName = name;
}

void Player::SetColor(const Player::Color& color)
{
	this->m_color = color;
}

void Player::SetScore(const size_t& score)
{
	this->m_score = score;
}

void Player::SetTerritoriesCount(const int& territoriesCount)
{
	this->m_territoriesCount = territoriesCount;
}

void Player::AddScore(size_t score)
{
	this->m_score = score;
}

Player& Player::operator=(const Player& other)
{
	if (this == &other)
	{
		return *this;
	}
	this->m_score = other.m_score;
	this->m_territoriesCount = other.m_territoriesCount;
	this->m_color = other.m_color;
	this->m_playerName = other.m_playerName;
	return *this;
}

Player& Player::operator=(Player&& other) noexcept
{
	m_playerName = std::exchange(other.m_playerName, std::string());
	m_color = std::exchange(other.m_color, Player::Color::NaN);
	m_score = std::exchange(other.m_score, 0);
	m_territoriesCount = std::exchange(other.m_territoriesCount, 0);
	return *this;
}

bool Player::operator<(const Player& other)
{
	return this->m_score < other.m_score;
}
