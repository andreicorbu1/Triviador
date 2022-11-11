#include "Board.h"

Board::Board(std::size_t width, std::size_t height)
{
    m_width = width;
    m_height = height;
    m_board.resize(width * height);
}

const std::optional<Territory>& Board::operator[](Position pos) const
{
    const auto& [line, column] = pos;
    return m_board[line * m_width + column];
}

std::optional<Territory>& Board::operator[](Position pos)
{
    const auto& [line, column] = pos;
    return m_board[line * m_width + column];
}

std::ostream& operator<<(std::ostream& out, const Board& b)
{
    Board::Position pos;
    auto& [line, column] = pos;
    for (line = 0; line < b.m_height; line++) {
        for (column = 0; column < b.m_width; column++) {
            if (b[pos])
                out << "Player1[1000]";
            else
                out << "[___]";
            out << "  ";
        }
        out << "\n\n";
    }

    return out;
}