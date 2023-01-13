#include "Board.h"

Board::Board(const std::size_t& width, const std::size_t& height)
	: m_width(width)
	, m_height(height)
	, m_board(width * height, std::make_shared<Territory>())
{
	// empty
}

Board::Board(const Board& other)
{
	*this = other;
}

Board::Board(Board&& other) noexcept
{
	*this = std::move(other);
}

const std::shared_ptr<Territory>& Board::operator[](size_t pos) const
{
	if (pos >= m_board.size())
	{
		throw std::out_of_range("Position is out of range!");
	}
	return m_board[pos];
}

std::vector<std::shared_ptr<Territory>> Board::GetTerritories() const
{
	return m_board;
}

std::vector<std::shared_ptr<Territory>>& Board::GetTerritories()
{
	return m_board;
}

size_t Board::GetWidth() const
{
	return m_width;
}

size_t Board::GetHeight() const
{
	return m_height;
}

std::shared_ptr<Territory>& Board::operator[](size_t pos)
{
	if (pos >= m_board.size())
	{
		throw std::out_of_range("Position is out of range!");
	}
	return m_board[pos];
}

Board& Board::operator=(const Board& other)
{
	if (this != &other)
	{
		m_board.clear();
		for (auto& territory : other.m_board)
		{
			m_board.push_back(std::make_shared<Territory>(*territory));
		}
		this->m_height = other.m_height;
		this->m_width = other.m_width;
	}
	return *this;
}

Board& Board::operator=(Board&& other) noexcept
{
	if (this != &other)
	{
		m_board = std::exchange(other.m_board, {});
		m_height = std::exchange(other.m_height, 0);
		m_width = std::exchange(other.m_width, 0);
	}
	return *this;
}