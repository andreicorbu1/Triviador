#include "Game.h"

Game::Game(const Player& player1, const Player& player2)
    : m_board(3, 3)
    , m_players{ player1, player2 }
    , m_gameRounds(5)
{
    // empty
}

Game::Game(const Player& player1, const Player& player2, const Player& player3)
    : m_board(5, 3)
    , m_players{ player1, player2, player3 }
    , m_gameRounds(4)
{
    // empty
}

Game::Game(const Player& player1, const Player& player2, const Player& player3, const Player& player4)
    : m_board(6, 4)
    , m_players{ player1, player2, player3, player4 }
    , m_gameRounds(4)
{
    // empty
}

const Board& Game::GetBoard() const
{
    return m_board;
}

void Game::Start()
{
    // empty
}
