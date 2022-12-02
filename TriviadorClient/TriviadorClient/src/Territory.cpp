#include "Territory.h"

Territory::Territory()
    : m_score(kBaseScore)
{
    m_shape.setWidth(rectangularSize);
    m_shape.setHeight(rectangularSize);
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

void Territory::SetTerritoryCoordinates(int x, int y)
{
    m_shape.setX(x);
    m_shape.setY(y);
}

const QRect Territory::GetShape() const
{
    return m_shape;
}

Territory& Territory::operator=(const Territory& territory)
{
    m_owner = territory.m_owner;
    m_score = territory.m_score;
    return *this;
}

Territory& Territory::operator=(Territory&& territory) noexcept
{
    m_owner = territory.m_owner;
    m_score = territory.m_score;
    new(&territory)Territory;
    return *this;
}

std::ostream& operator<< (std::ostream& out, const Territory& t)
{
    out << (t.m_owner.has_value() ? t.m_owner.value().GetName() : "No owner");
    out << "[" << t.m_score << "]";
    return out;
}
