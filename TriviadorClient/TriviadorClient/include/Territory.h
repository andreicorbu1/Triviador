#pragma once
#include "Player.h"
#include "qrect.h"
#include <iostream>
#include <optional>

class Territory : public QRect
{
public:
    Territory();
    explicit Territory(const Player& owner);
    Territory(const Player& owner, const bool& isBase);
    Territory(const Territory& territory);
    Territory(Territory&& territory) noexcept;
    ~Territory() = default;
    
    void SetTerritoryCoordinates(int x, int y);
    const QRect GetShape() const;
    
    // Operators:
    Territory& operator=(const Territory& territory);
    Territory& operator=(Territory&& territory) noexcept;

    friend std::ostream& operator<< (std::ostream& out, const Territory& t);

private:
    const uint16_t kBaseScore = 300;
    const uint16_t kTerritoryScore = 100;
    const uint16_t rectangularSize = 100;
    
private:
    std::optional<Player> m_owner;
    uint16_t m_score;
    QRect m_shape;
};

