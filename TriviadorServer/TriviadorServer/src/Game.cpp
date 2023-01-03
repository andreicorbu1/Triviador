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

uint16_t Game::GetRounds() const
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

std::pair<NumericalAnswerQuestion, uint16_t> Game::GetNumericalAnswerQuestion()
{
	if (numericQuestionIndex < m_numericalAnswerQuestions.size())
	{
		return {m_numericalAnswerQuestions[numericQuestionIndex++], numericQuestionIndex - 1};
	}
	else
	{
		throw std::out_of_range("All numerical questions have been selected");
	}
}

NumericalAnswerQuestion Game::GetNumericalAnswerQuestion(uint16_t index) const
{
	if (index < m_numericalAnswerQuestions.size())
	{
		return m_numericalAnswerQuestions[index];
	}
	else
	{
		throw std::out_of_range("All numerical questions have been selected");
	}
}

std::pair<MultipleAnswerQuestion, uint16_t> Game::GetMultipleAnswerQuestion()
{
	if (multipleQuestionIndex < m_multipleAnswerQuestions.size())
	{
		return {m_multipleAnswerQuestions[multipleQuestionIndex++], multipleQuestionIndex - 1};
	}
	else
	{
		throw std::out_of_range("All multiple questions have been selected");
	}
}

MultipleAnswerQuestion Game::GetMultipleAnswerQuestion(uint16_t index) const
{
	if (index < m_multipleAnswerQuestions.size())
	{
		return m_multipleAnswerQuestions[index];
	}
	else
	{
		throw std::out_of_range("All multiple questions have been selected");
	}
}

std::string Game::CurrentStage() const
{
	switch (m_currentStage)
	{
		case Stage::Stage1:
			return "Stage 1";
			break;
		case Stage::Stage2:
			return "Stage 2";
			break;
		case Stage::Stage3:
			return "Stage 3";
			break;
		case Stage::Stage4:
			return "Stage 4";
			break;
		default:
			throw std::invalid_argument("Stage invalid");
	}
}

void Game::SetBoard(const Board& board)
{
	this->m_board = board;
}

void Game::SetPlayers(const std::vector<Player>& players)
{
	this->m_players = players;
}

void Game::SetRounds(const uint16_t& rounds)
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

void Game::GoToNextStage()
{
	switch (m_currentStage)
	{
		case Stage::Stage1:
			m_currentStage = Stage::Stage2;
			break;
		case Stage::Stage2:
			m_currentStage = Stage::Stage3;
			break;
		case Stage::Stage3:
			m_currentStage = Stage::Stage4;
			break;
		default:
			throw std::invalid_argument("Cannot advance in other stages because you are in a final stage");
	}

}

Game& Game::operator=(const Game& other)
{
	if (this != &other)
	{
		m_board = other.m_board;
		m_gameRounds = other.m_gameRounds;
		m_ID = other.m_ID;
		m_players = other.m_players;
		return *this;
	}
}

void Game::Start()
{
	m_currentStage = Stage::Stage1;
}

void Game::AddToAnswered(int questionId, const Player& player)
{
	if (m_alreadyAnswered.size() == m_players.size())
	{
		throw std::range_error("All players have already answered the question");
		return;
	}
	m_alreadyAnswered[questionId].push_back(player);
}

void Game::Cleanup()
{
	m_questionManager.Clear();
	m_players.clear();
	m_multipleAnswerQuestions.clear();
	m_numericalAnswerQuestions.clear();
}

void Game::ChooseBaseTerritories(const std::vector<std::pair<Player, std::pair<int, int>>>& players)
{
	for (const auto& player : players)
	{
		m_board[player.second] = Territory(player.first, true);
	}
	GoToNextStage();
}

void Game::ChooseTerritories(const std::vector<std::pair<Player, std::vector<std::pair<int, int>>>>& playersOrder)
{
	for (size_t idx = 0; idx < playersOrder.size(); ++idx)
	{
		for (size_t idx2 = 0; idx < playersOrder[idx].second.size() && (m_players.size() - idx - 1) == playersOrder[idx].second.size(); ++idx2)
		{
			if (m_board[playersOrder[idx].second[idx2]].GetOwner().has_value())
			{
				throw std::invalid_argument("Territory already ocuppied");
			}
			else
			{
				m_board[playersOrder[idx].second[idx2]] = Territory(playersOrder[idx].first);
			}
		}
	}
}
