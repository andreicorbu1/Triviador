#include "Game.h"

Game::Game(const Player& player1, const Player& player2)
	: m_board(3, 3)
	, m_players{player1, player2}
	, m_gameRounds(5)
	, m_ID(-1)
{
	// empty
}

Game::Game(const Player& player1, const Player& player2, const Player& player3)
	: m_board(5, 3)
	, m_players{player1, player2, player3}
	, m_gameRounds(4)
	, m_ID(-1)
{
	// empty
}

Game::Game(const Player& player1, const Player& player2, const Player& player3, const Player& player4)
	: m_board(6, 4)
	, m_players{player1, player2, player3, player4}
	, m_gameRounds(5)
	, m_ID(-1)
{
	//empty
}

Game::Game(const Game& other)
{
	*this = other;
}

Board Game::GetBoard() const
{
	return m_board;
}

std::vector<Player> Game::GetPlayers() const
{
	return m_players;
}

int Game::GetRounds() const
{
	return m_gameRounds;
}

int32_t Game::GetGameID()
{
	return m_ID;
}

Player Game::GetWinner() const
{
	auto copyOfPlayers(m_players);
	std::ranges::sort(copyOfPlayers, std::less());
	return copyOfPlayers.back();
}

void Game::SetBoard(const Board& board)
{
	this->m_board = board;
}

void Game::SetPlayers(const std::vector<Player>& players)
{
	this->m_players = players;
}

void Game::SetRounds(const int& rounds)
{
	this->m_gameRounds = rounds;
}

void Game::SetGameID(const int32_t& gameID)
{
	this->m_ID = gameID;
}

Game& Game::operator=(const Game& other)
{
	m_board = other.m_board;
	m_gameRounds = other.m_gameRounds;
	m_ID = other.m_ID;
	m_players = other.m_players;
	return *this;
}

void Game::Start()
{
	ChooseBaseTerritories();
	std::cout << m_board;
}

void Game::ChooseBaseTerritories()
{
	for (const auto& player : m_players)
	{
		do
		{
			std::cout << m_board << std::endl;
			std::cout << player.GetName() << ", choose a territory: ";
			uint16_t line;
			uint16_t column;
			std::cin >> line >> column;

			try
			{
				Board::Position pos = {line, column};
				if (m_board[pos].GetOwner().has_value())
				{
					std::cerr << "This territory is already taken!\n";
				}
				else
				{
					m_board[pos] = Territory(player, true);
					break;
				}
			}
			catch (const std::out_of_range& e)
			{
				std::cerr << e.what() << "\n";
			}
		} while (true);
	}
}
