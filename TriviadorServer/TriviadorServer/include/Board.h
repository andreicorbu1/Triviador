#pragma once
#include "Territory.h"

#include <vector>
#include <optional>

class Board
{
public:
    using Position = std::pair<uint8_t, uint8_t>;

public:
    Board() = default;
    Board(const size_t& width, const size_t& height);
    Board(const Board& other);
    Board(Board&& other) noexcept;
    ~Board() = default;
    // Setters:
    Territory& operator[] (Position pos);
    
    // Getters:
    const Territory& operator[] (Position pos) const;

    // Operators:
    friend std::ostream& operator<< (std::ostream& out, const Board& b);
    Board& operator=(const Board& other);
    Board& operator=(Board&& other) noexcept;

private:
    std::vector<Territory> m_board;
    size_t m_width;
    size_t m_height;
};

