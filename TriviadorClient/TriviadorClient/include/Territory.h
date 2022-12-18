#pragma once
#include "Player.h"
#include <iostream>
#include <optional>
#include <QPushButton>

class Territory 
{
public:
    Territory() = default;
    Territory(QWidget* parent);
    //explicit Territory(const Player& owner);
    //Territory(const Player& owner, const bool& isBase);
    Territory(const Territory& territory);
    Territory(Territory&& territory) noexcept;
    ~Territory();
    //
    //// Operators:
    Territory& operator=(const Territory& territory);
    Territory& operator=(Territory&& territory) noexcept;

    //friend std::ostream& operator<< (std::ostream& out, const Territory& t);

    void setGeometry(int x, int y, int width, int height);
    void setMask(const QPixmap& mask);
    void SetButtonProperties();

private slots:
    void m_buttonClicked();

private:
    const uint16_t kBaseScore = 300;
    const uint16_t kTerritoryScore = 100;

private:
    Player m_owner;
    uint16_t m_score;
    QPushButton* m_button;
};

