#include "Board.h"

Board::Board(const std::size_t& width, const std::size_t& height)
    : kWidth(width)
    , kHeight(height)
{
    m_board.resize(kWidth * kHeight);
}

//Board::Board(const Board& other)
//{
//    *this = other;
//}
//
//Board::Board(Board&& other) noexcept
//{
//    *this = std::move(other);
//}


const std::optional<Territory>& Board::operator[](Position pos) const
{
    const auto& [line, column] = pos;
    
    if (line >= kHeight || column >= kWidth) {
        throw std::out_of_range("Position is out of range!");
    }
    
    return m_board[line * kWidth + column];
}
//
//Board& Board::operator=(const Board& other)
//{
//    this->m_board = other.m_board;
//    return *this;
//}
//
//Board& Board::operator=(Board&& other) noexcept
//{
//    this->m_board = other.m_board;
//    //new(&other) Board;
//    return *this;
//}

std::optional<Territory>& Board::operator[](Position pos)
{
    const auto& [line, column] = pos;
    
    if (line >= kHeight || column >= kWidth) {
        throw std::out_of_range("Position is out of range!");
    }
    
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