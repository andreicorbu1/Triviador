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

    static Color ToColor(std::string color);
	static std::string ToString(Color color);

public:
    Player() = default;
    Player(const std::string& playerName, const Color& color);
    Player(const Player& other);
    Player(Player&& other) noexcept;
    ~Player() = default;

    // Getters:
	const std::string& GetName() const;
	Player::Color GetColor() const;
	uint16_t GetScore() const;

	// Setters:
    void SetName(const std::string& name);
    void SetColor(const Player::Color& color);
    void SetScore(const uint16_t& score);

    // Operators:
    Player& operator =(const Player& other);
    Player& operator =(Player&& other) noexcept;
    bool operator <(const Player& other);

private:
    std::string m_playerName;
    Color m_color;
    uint16_t m_score;
};

