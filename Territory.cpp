#include "Territory.h"

Territory::Territory(std::string owner)
    : m_owner(owner), m_score(baseScore)
{
    // empty
}

Territory::Territory(const Territory& territory)
{
    *this = territory;
}

Territory& Territory::operator=(const Territory& territory)
{
    m_owner = territory.m_owner;
    m_score = territory.m_score;
    return *this;
}

std::ostream& operator<< (std::ostream& out, const Territory& t)
{
    out << t.m_owner << "[" << t.m_score << "]";
    return out;
}
