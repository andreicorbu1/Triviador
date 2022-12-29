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
    Territory& operator[] (int pos);
    
    // Getters:
    Territory operator[] (Position pos) const;
    Territory operator[] (int pos) const;

    // Operators:
	Board& operator= (const Board& other);
	Board& operator= (Board&& other) noexcept;
	// friend std::ostream& operator<< (std::ostream& out, const Board& board);


    void Set2PGame();
    void Set3PGame();
    void Set4PGame();

    void ResizeBoard(QSize oldWindowSize, QSize newWindowSize);
    int Size();

private:
    void GetMasks(int playersNumber);
    void SetMasks();
    void SetGeometry2PGame();
    void SetGeometry4PGame();
    float RuleOfThree(float oldValue, float oldSize, float newSize);

private:
    std::size_t m_width;
    std::size_t m_height;
    std::size_t m_size;
    const QSize m_originalWindowSize = QSize(1491, 807);

private:
    std::vector<Territory> m_board;
    std::vector<QPixmap> m_masks;
};

