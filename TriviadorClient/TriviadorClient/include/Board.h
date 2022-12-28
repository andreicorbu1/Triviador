#pragma once
#include "Territory.h"
#include <qpainter.h>
#include <vector>
#include <optional>
#include <algorithm>
#include "qscreen.h"

class Board
{
public:
    using Position = std::pair<uint8_t, uint8_t>;

public:
	Board();
    Board(const std::size_t& width, const std::size_t& height, QWidget* parent = nullptr);
	Board(const Board& other);
	Board(Board&& other) noexcept;
	~Board();
    
    // Setters:
    Territory& operator[] (Position pos);
    
    // Getters:
    const Territory& operator[] (Position pos) const;
    const Territory& operator[] (int pos) const;

    // Operators:
	Board& operator= (const Board& other);
	Board& operator= (Board&& other) noexcept;
	// friend std::ostream& operator<< (std::ostream& out, const Board& board);


    void Set2PGame();
    void Set3PGame();
    void Set4PGame();
    int Size();

private:
    void SetMasks(int playersNumber);
    void SetGeometry2PGame();
    void SetGeometry4PGame();

private slots:
    void on_territoryButton_clicked();

private:
    std::size_t m_width;
    std::size_t m_height;
    std::size_t m_size;

private:
    std::vector<Territory> m_board;
};

