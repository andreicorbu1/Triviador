#pragma once
#include <string>

class Player
{
public:
    enum class Color
    {
        None,
        Blue,
        Red,
        Green,
        Yellow
    };

public:
    Player();
    Player(const std::string& playerName, const Color& color);
    Player(const Player& other);
    ~Player() = default;

    // Getters:
    const std::string& GetName() const;

    // Operators:
    Player& operator =(const Player& other);
    Player& operator+=(int score);

private:
    std::string m_playerName;
    Color m_color;
    size_t m_score;
    int m_territoriesCount;
};

