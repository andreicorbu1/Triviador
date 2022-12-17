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
	Board();
    Board(const std::size_t& width, const std::size_t& height);
	Board(const Board& other);
	Board(Board&& other) noexcept;
	~Board();
    
    // Setters:
    Territory& operator[] (Position pos);
    
    // Getters:
    const Territory& operator[] (Position pos) const;

    // Operators:
	Board& operator= (const Board& other);
	Board& operator= (Board&& other) noexcept;
	// friend std::ostream& operator<< (std::ostream& out, const Board& board);

    void SetMasksForFourPlayersGame();
    void SetCoordinatesForFourPlayersGame();
    void ShowButtons();
private:
    std::size_t m_width;
    std::size_t m_height;
    std::size_t m_size = m_width * m_height;

private:
    std::vector<Territory> m_board{ m_size };
};

