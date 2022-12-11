#pragma once
#include "Territory.h"
#include <qpainter.h>
#include <vector>
#include <optional>
#include <algorithm>

class Board
{
public:
    using Position = std::pair<uint8_t, uint8_t>;

public:
    Board(const std::size_t& width, const std::size_t& height);

    // Setters:
    Territory& operator[] (Position pos);
    
    // Getters:
    const Territory& operator[] (Position pos) const;

    // Operators:
    //friend std::ostream& operator<< (std::ostream& out, const Board& b);

    void SetMasksForFourPlayersGame();
    void SetCoordinatesForFourPlayersGame();
    void ShowButtons();
private:
    // Constants:
    const std::size_t kWidth;
    const std::size_t kHeight;
    const std::size_t kSize = kWidth * kHeight;

private:
    std::vector<Territory> m_board{ kSize };
};

