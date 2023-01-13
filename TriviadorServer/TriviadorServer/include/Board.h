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
	Board(const size_t& height, const size_t& width);
	Board(const Board& other);
	Board(Board&& other) noexcept;
	~Board() = default;
	// Setters
	Territory& operator[] (size_t pos);

	// Getters:
	Territory operator[] (size_t pos) const;
	std::vector<Territory> GetTerritories() const;
	size_t GetWidth() const;
	size_t GetHeight() const;

	// Operators:
	Board& operator=(const Board& other);
	Board& operator=(Board&& other) noexcept;

private:
	std::vector<Territory> m_board;
	size_t m_width;
	size_t m_height;
};

