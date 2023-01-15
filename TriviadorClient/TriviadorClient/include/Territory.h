#pragma once
#include <QPainter>
#include <QPushButton>
#include <QScreen>

#include "Player.h"

class Territory
{
public:
    Territory() = default;
    Territory(QWidget* parent);
    Territory(const Territory& territory);
    Territory(Territory&& territory) noexcept;
    ~Territory();

    // Setters:
    void SetGeometry(int x, int y, int width, int height);
    void SetMask(const QPixmap& mask);
	void SetOwner(const Player& player);
	void SetScore(const int& score);
    void SetBaseIcon(const QPixmap& baseIcon);
    
	// Getters:
    QPushButton* getButton() const;
    Player GetOwner() const;
    
    // Methods:
    void Update();

    // Operators:
    Territory& operator=(const Territory& territory);
    Territory& operator=(Territory&& territory) noexcept;

private:
    const uint16_t kBaseScore = 300;
    const uint16_t kTerritoryScore = 100;

private:
    Player m_owner;
    uint16_t m_score;
    QPushButton* m_button;
};

