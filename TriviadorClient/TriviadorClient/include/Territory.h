#pragma once
#include "Player.h"
#include "qrect.h"
#include <iostream>
#include <optional>

class Territory
{
public:
    Territory();
    explicit Territory(const Player& owner);
    Territory(const Player& owner, const bool& isBase);
    Territory(const Territory& territory);
    Territory(Territory&& territory) noexcept;
    ~Territory() = default;
    
    // Operators:
    Territory& operator=(const Territory& territory);
    Territory& operator=(Territory&& territory) noexcept;

    friend std::ostream& operator<< (std::ostream& out, const Territory& t);

    void SetRectangularCoordinates(int x, int y);
    void SetRectangularSize(int height, int width);
    QRect GetRectangular();

private:
    const uint16_t kBaseScore = 300;
    const uint16_t kTerritoryScore = 100;
    
private:
    std::optional<Player> m_owner;
    uint16_t m_score;
    QRect m_rect;
};

