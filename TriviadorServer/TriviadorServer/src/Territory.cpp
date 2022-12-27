#include "Territory.h"

Territory::Territory()
	: m_score(kBaseScore)
{
	// empty
}

Territory::Territory(const Player& owner)
	: m_owner(owner)
	, m_score(kTerritoryScore)
{
	// empty
}

Territory::Territory(const Player& owner, const bool& isBase)
	: m_owner(owner)
	, m_score(kBaseScore)
{
	// empty
}

Territory::Territory(const Territory& territory)
{
	*this = territory;
}

Territory::Territory(Territory&& territory) noexcept
{
	*this = std::move(territory);
}

std::optional<Player> Territory::GetOwner() const
{
	return m_owner;
}

uint16_t Territory::GetScore() const
{
	return m_score;
}

void Territory::SetOwner(const std::optional<Player>& owner)
{
	m_owner = owner;
}

void Territory::SetScore(const uint16_t& score)
{
	m_score = score;
}

Territory& Territory::operator=(const Territory& territory)
{
	m_owner = territory.m_owner;
	m_score = territory.m_score;
	return *this;
}

Territory& Territory::operator=(Territory&& territory) noexcept
{
	m_owner = std::exchange(territory.m_owner, std::string());
	m_score = std::exchange(territory.m_score, 0);
	return *this;
}

std::ostream& operator<< (std::ostream& out, const Territory& t)
{
	out << (t.m_owner.has_value() ? t.m_owner.value().GetName() : "No owner");
	out << "[" << t.m_score << "]";
	return out;
}
