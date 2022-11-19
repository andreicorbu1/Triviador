#pragma once

#include "Board.h"
#include "Player.h"
// #include "QuestionManager.h"

class Game
{
public:
    Game(const Player& player1, const Player& player2);
    Game(const Player& player1, const Player& player2, const Player& player3);
    Game(const Player& player1, const Player& player2, const Player& player3, const Player& player4);
    ~Game() = default;

    // Methods:
    void Start();

private:
    Board m_board;
    std::vector<Player> m_players;
    // QuestionManager m_questionManager;
};

