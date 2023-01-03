#include "Game.h"

QuestionManager Game::m_questionManager("resource/Questions.sqlite");

Game::Game(const std::vector<Player>& players) : m_players(players)
{
	switch (players.size())
	{
		case 2:
			m_board = Board(3, 3);
			m_gameRounds = 5;
			break;
		case 3:
			m_board = Board(5, 3);
			m_gameRounds = 4;
			break;
		case 4:
			m_board = Board(6, 4);
			m_gameRounds = 5;
			break;
		default:
			throw std::out_of_range("Invalid number of players");
			break;
	}
	m_ID = -1;
	SetQuestions(players.size());
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

int32_t Game::GetGameID() const
{
	return m_ID;
}

Player Game::GetWinner()
{
	auto copyOfPlayers(m_players);
	std::ranges::sort(copyOfPlayers, std::less());
	Cleanup();
	return copyOfPlayers.back();
}

NumericalAnswerQuestion Game::GetNumericalAnswerQuestion()
{
	if (numericQuestionIndex < m_numericalAnswerQuestions.size())
		return m_numericalAnswerQuestions[numericQuestionIndex++];
}

MultipleAnswerQuestion Game::GetMultipleAnswerQuestion()
{
	if (multipleQuestionIndex < m_multipleAnswerQuestions.size())
		return m_multipleAnswerQuestions[multipleQuestionIndex++];
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

void Game::SetQuestions(const uint16_t& numberOfPlayers)
{
	std::random_device rd;
	std::mt19937 gen{rd()};
	uint16_t questionIndex;
	switch (numberOfPlayers)
	{
		case 2:
			m_numericalAnswerQuestions.resize(kTwoPlayersNumericAnswerQuestions);
			m_multipleAnswerQuestions.resize(kTwoPlayersMultipleAnswerQuestions);
			for (size_t index = 0; index < kTwoPlayersNumericAnswerQuestions; ++index)
			{
				questionIndex = m_questionManager.GetRandomNumericalAnswerQuestionsID();
				m_numericalAnswerQuestions[index] = m_questionManager.GetNumericalAnswerQuestion(questionIndex);
			}
			for (size_t index = 0; index < kTwoPlayersMultipleAnswerQuestions; ++index)
			{
				questionIndex = m_questionManager.GetRandomMultipleAnswerQuestionsID();
				m_multipleAnswerQuestions[index] = m_questionManager.GetMultipleAnswerQuestion(questionIndex);
			}
			break;

		case 3:
			m_numericalAnswerQuestions.resize(kThreePlayersNumericAnswerQuestions);
			m_multipleAnswerQuestions.resize(kThreePlayersMultipleAnswerQuestions);
			for (size_t index = 0; index < kThreePlayersNumericAnswerQuestions; ++index)
			{
				questionIndex = m_questionManager.GetRandomNumericalAnswerQuestionsID();
				m_numericalAnswerQuestions[index] = m_questionManager.GetNumericalAnswerQuestion(questionIndex);
			}

			for (size_t index = 0; index < kThreePlayersMultipleAnswerQuestions; ++index)
			{
				questionIndex = m_questionManager.GetRandomMultipleAnswerQuestionsID();
				m_multipleAnswerQuestions[index] = m_questionManager.GetMultipleAnswerQuestion(questionIndex);
			}
			break;

		case 4:
			m_numericalAnswerQuestions.resize(kFourPlayersNumericAnswerQuestions);
			m_multipleAnswerQuestions.resize(kFourPlayersMultipleAnswerQuestions);
			for (size_t index = 0; index < kFourPlayersNumericAnswerQuestions; ++index)
			{
				questionIndex = m_questionManager.GetRandomNumericalAnswerQuestionsID();
				m_numericalAnswerQuestions[index] = m_questionManager.GetNumericalAnswerQuestion(questionIndex);
			}
			for (size_t index = 0; index < kFourPlayersMultipleAnswerQuestions; ++index)
			{
				questionIndex = m_questionManager.GetRandomMultipleAnswerQuestionsID();
				m_multipleAnswerQuestions[index] = m_questionManager.GetMultipleAnswerQuestion(questionIndex);
			}
			break;
		default:
			throw std::out_of_range("Invalid number of players");
	}
	std::ranges::shuffle(m_numericalAnswerQuestions, gen);
	std::ranges::shuffle(m_multipleAnswerQuestions, gen);
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

void Game::Cleanup()
{
	m_questionManager.Clear();
	m_players.clear();
	m_multipleAnswerQuestions.clear();
	m_numericalAnswerQuestions.clear();
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
