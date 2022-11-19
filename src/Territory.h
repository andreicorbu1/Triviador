#pragma once
#include "Player.h"

#include <iostream>
#include <optional>

class Territory
{
public:
    Territory();
    explicit Territory(const Player& owner);
    Territory(const Territory& territory);
    Territory(Territory&& territory) noexcept;
    ~Territory() = default;
    
    // Operators:
    Territory& operator=(const Territory& territory);
    Territory& operator=(Territory&& territory) noexcept;

    friend std::ostream& operator<< (std::ostream& out, const Territory& t);

private:
    const uint16_t kBaseScore = 100;
    
private:
    std::optional<Player> m_owner;
    uint16_t m_score;
};

