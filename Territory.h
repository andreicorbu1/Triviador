#pragma once

#include <iostream>

class Territory
{
public:
    Territory(std::string owner);
    Territory(const Territory& territory);

    Territory& operator=(const Territory& territory);

    friend std::ostream& operator<< (std::ostream& out, const Territory& t);

private:
    const uint16_t baseScore = 100;

private:
    std::string m_owner;
    uint16_t m_score;
};

