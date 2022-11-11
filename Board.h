#pragma once
#include "Territory.h"

#include <vector>
#include <optional>

class Board
{
public:
    using Position = std::pair<uint8_t, uint8_t>;

public:
    Board(std::size_t width, std::size_t height);

    // Getter
    const std::optional<Territory>& operator[] (Position pos) const;
    // Setter
    std::optional<Territory>& operator[] (Position pos);

    friend std::ostream& operator<< (std::ostream& out, const Board& b);

private:
    std::size_t m_width;
    std::size_t m_height;

private:
    std::vector<std::optional<Territory>> m_board;
};

