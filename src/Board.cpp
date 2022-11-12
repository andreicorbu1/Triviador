#include "Board.h"

Board::Board(const std::size_t& width, const std::size_t& height)
    : kWidth(width)
    , kHeight(height)
{
    // empty
}

const std::optional<Territory>& Board::operator[](Position pos) const
{
    const auto& [line, column] = pos;
    return m_board[line * kWidth + column];
}

std::optional<Territory>& Board::operator[](Position pos)
{
    const auto& [line, column] = pos;
    return m_board[line * kWidth + column];
}

std::ostream& operator<<(std::ostream& out, const Board& b)
{
    Board::Position pos;
    auto& [line, column] = pos;
    for (line = 0; line < b.kHeight; line++) {
        for (column = 0; column < b.kWidth; column++) {
            if (b[pos])
                out << *b[pos];
            else
                out << "[____]";
            out << "  ";
        }
        out << "\n\n";
    }

    return out;
}