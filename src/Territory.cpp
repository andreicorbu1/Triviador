#include "Territory.h"

Territory::Territory()
    : m_owner(nullptr)
    , m_score(kBaseScore)
{
    // empty
}

Territory::Territory(const std::string& owner)
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
    out << t.m_owner << "[" << t.m_score << "]";
    return out;
}
