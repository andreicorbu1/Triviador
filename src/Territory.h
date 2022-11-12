#pragma once

#include <iostream>

class Territory
{
public:
    Territory();
    explicit Territory(const std::string& owner);
    Territory(const Territory& territory);
    Territory(Territory&& territory) noexcept;
    ~Territory() = default;

    Territory& operator=(const Territory& territory);
    Territory& operator=(Territory&& territory) noexcept;

    friend std::ostream& operator<< (std::ostream& out, const Territory& t);

private:
    const uint16_t kBaseScore = 100;

private:
    std::string m_owner;
    uint16_t m_score;
};

