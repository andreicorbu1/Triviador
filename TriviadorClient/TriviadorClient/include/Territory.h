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
    Territory(const Territory& territory);
    Territory(Territory&& territory) noexcept;
    ~Territory();

    // Operators:
    Territory& operator=(const Territory& territory);
    Territory& operator=(Territory&& territory) noexcept;

    // Setters:
    void setGeometry(int x, int y, int width, int height);
    void setMask(const QPixmap& mask);
	void SetOwner(const Player& player);
	void SetScore(const int& score);
    void SetIcon(QPixmap& icon);
    
	// Getters:
    QPushButton* getButton() const;
    
    // Methods:
    void Update();

private:
    const uint16_t kBaseScore = 300;
    const uint16_t kTerritoryScore = 100;

private:
    Player m_owner;
    uint16_t m_score;
    QPushButton* m_button;
};

