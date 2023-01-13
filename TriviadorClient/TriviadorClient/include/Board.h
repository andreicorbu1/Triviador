#pragma once
#include "Territory.h"

class Board
{
public:
	Board();
    Board(const std::size_t& height, const std::size_t& width, QWidget* parent = nullptr);
	Board(const Board& other);
	Board(Board&& other) noexcept;
	~Board();
    
    // Setters:
    Territory& operator[] (int pos);
    
    // Getters:
    Territory operator[] (int pos) const;

    // Operators:
	Board& operator= (const Board& other);
	Board& operator= (Board&& other) noexcept;

    void Set2PGame();
    void Set3PGame();
    void Set4PGame();
    int Size();

private:
    void SetMasks(int playersNumber);
    void SetGeometry2PGame();
    void SetGeometry3PGame();
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

