#pragma once
#include "Board.h"
#include "Player.h"
class Game
{
public:
    Game(const Player& player1, const Player& player2);
    Game(const Player& player1, const Player& player2, const Player& player3);
    Game(const Player& player1, const Player& player2, const Player& player3, const Player& player4);
    ~Game() = default;

    // Getters:
    Board GetBoard() const;

    // Methods:
    void Start();

private:
    void ChooseBaseTerritories();

private:
	Board m_board;
	std::vector<Player> m_players;
	int m_gameRounds;
	int32_t m_ID;
};

