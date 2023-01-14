#include "Game.h"

QuestionManager Game::m_questionManager("resource/Questions.sqlite");

Game::Game(const std::vector<Player>& players) : m_players(players)
{
	switch (players.size())
	{
	case 2:
		m_board = Board(3, 3);
		m_gameRounds = 5;
		m_chooseTerritoryRoundsNumber = 7;
		m_duelRoundsNumber = 10;
		break;
	case 3:
		m_board = Board(5, 3);
		m_gameRounds = 4;
		m_chooseTerritoryRoundsNumber = 4;
		m_duelRoundsNumber = 12;
		break;
	case 4:
		m_board = Board(6, 4);
		m_gameRounds = 5;
		m_chooseTerritoryRoundsNumber = 4;
		m_duelRoundsNumber = 20;
		break;
	default:
		throw std::out_of_range("Invalid number of players");
		break;
	}
	m_ID = -1;
	SetQuestions(players.size());
	SetStagesForChooseBase();
	SetStagesForChooseTerritory();
	SetStagesForDuel();
	m_stages.push_back(Stage::Result);
	m_currentStageIndex = 0;
	m_currentStage = m_stages[0];
	//m_duelParticipants.resize(2);
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

std::vector<Player>& Game::GetPlayers()
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

uint16_t Game::GetCurrentNumericalAnswerQuestionIndex() const
{
	return numericQuestionIndex;
}

uint16_t Game::GetCurrentMultipleAnswerQuestionIndex() const
{
	return multipleQuestionIndex;
}

std::pair<NumericalAnswerQuestion, uint16_t> Game::GetNumericalAnswerQuestion()
{
	if (numericQuestionIndex < m_numericalAnswerQuestions.size())
	{
		return { m_numericalAnswerQuestions[numericQuestionIndex++], numericQuestionIndex - 1 };
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

std::pair<NumericalAnswerQuestion, uint16_t> Game::GetNewNumericalAnswerQuestion()
{
	m_playersWhoSentRequest.clear();
	if (numericQuestionIndex < m_numericalAnswerQuestions.size())
	{
		return { m_numericalAnswerQuestions[++numericQuestionIndex], numericQuestionIndex };
	}
	else
	{
		throw std::out_of_range("All numerical questions have been selected");
	}
}

NumericalAnswerQuestion Game::GetCurrentNumericalAnswerQuestion() const
{
	return m_numericalAnswerQuestions[numericQuestionIndex];
}

std::pair<MultipleAnswerQuestion, uint16_t> Game::GetMultipleAnswerQuestion()
{
	if (multipleQuestionIndex < m_multipleAnswerQuestions.size())
	{
		return { m_multipleAnswerQuestions[multipleQuestionIndex++], multipleQuestionIndex - 1 };
	}
	else
	{
		throw std::out_of_range("All multiple questions have been selected");
	}
}

std::pair<MultipleAnswerQuestion, uint16_t> Game::GetNewMultipleAnswerQuestion()
{
	m_playersWhoSentRequest.clear();
	if (multipleQuestionIndex < m_multipleAnswerQuestions.size())
	{
		return { m_multipleAnswerQuestions[++multipleQuestionIndex], multipleQuestionIndex };
	}
	else
	{
		throw std::out_of_range("All multiple questions have been selected");
	}
}

MultipleAnswerQuestion Game::GetCurrentMultipleAnswerQuestion()
{
	return m_multipleAnswerQuestions[multipleQuestionIndex];
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

std::string Game::GetCurrentStage() const
{
	switch (m_currentStage)
	{
	case Stage::NumericalAnswerQuestion:
		return "numericalAnswerQuestion";
		break;
	case Stage::MultipleAnswerQuestion:
		return "multipleAnswerQuestion";
		break;
	case Stage::ChooseBase:
		return "chooseBase";
		break;
	case Stage::ChooseTerritory:
		return "chooseTerritory";
		break;
	case Stage::Attack:
		return "attack";
		break;
	case Stage::Update:
		return "update";
		break;
	case Stage::Result:
		return "result";
		break;
	case Stage::Wait:
		return "wait";
		break;
	default:
		throw std::invalid_argument("Stage invalid");
	}
}

size_t Game::GetNumberOfPlayers() const
{
	return m_players.size();
}
const std::unordered_set<std::string>& Game::GetPlayersWhoSentRequest() const
{
	return m_playersWhoSentRequest;
}

const std::vector<Player>& Game::GetParticipants() const
{
	try
	{
		if (m_stages.at(m_currentStageIndex - 1) == Stage::Attack || m_stages.at(m_currentStageIndex - 2) == Stage::Attack)
		{
			return m_duelParticipants;
		}
	}
	catch (std::out_of_range ex) {}
	return m_players;
}

std::string Game::GetPlayerWhoWillMakeAChoice() const
{
	Participant participant = m_participantsQueue.top();
	std::string participantName = std::get<0>(participant);
	return participantName;
}

const Player& Game::GetCurrentAttacker()
{
	if (m_duelOrderIndex < 0)
	{
		m_duelOrderIndex = m_duelOrder.size()-1;
		std::random_device rd;
		std::ranges::shuffle(m_duelOrder, rd);
	}
	return m_duelOrder[m_duelOrderIndex];
}

uint16_t Game::GetParticipantsQueueSize() const
{
	return m_participantsQueue.size();
}

void Game::IncrementNumericalAnswerQuestionIndex()
{
	numericQuestionIndex++;
}

void Game::IncrementMultipleAnswerQuestionIndex()
{
	multipleQuestionIndex++;
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
	std::mt19937 gen{ rd() };
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
	m_playersWhoSentRequest.clear();
	m_currentStage = m_stages[++m_currentStageIndex];
}

void Game::AddNullPlayer()
{
	m_players.push_back(Player("", Player::Color::None));
}

void Game::SetAttackedPosition(uint16_t position)
{
	m_attackedPosition = position;
}

bool Game::AddTerritory(std::string username, int position, bool isBase)
{
	auto player = std::ranges::find_if(m_players, [&username](const Player& player)
		{
			return player.GetName() == username;
		});
	if (player != m_players.end())
	{
		if (!m_board[position].GetOwner().has_value())
		{
			if (isBase == false)
			{
				m_choosedTerritoryCounter++;
			}
			m_board[position] = isBase == true ? Territory(*player, isBase) : Territory(*player);
			return true;
		}
	}
	return false;
}

bool Game::PopPlayerWhoWillMakeAChoose()
{
	//GoToNextStage();
	if (m_currentStage == Stage::ChooseBase)
	{
		m_participantsQueue.pop();
		GoToNextStage();
		return true;
	}
	else if (m_currentStage == Stage::ChooseTerritory)
	{
		if (m_choosedTerritoryCounter == m_participantsQueue.size() - 1)
		{
			m_choosedTerritoryCounter = 0;
			m_participantsQueue.pop();
			if (m_participantsQueue.size() == 1)
			{
				m_participantsQueue.pop();
			}
			GoToNextStage();
			return true;
		}
	}
	GoToNextStage();
	return false;
}

void Game::DetermineDuelSituation(bool isMultiple)
{
	if (m_participantsQueue.size() == 2)
	{
		Participant participant1 = m_participantsQueue.top();
		m_participantsQueue.pop();
		Participant participant2 = m_participantsQueue.top();
		m_participantsQueue.pop();
		m_duelOrderIndex--;

		if (isMultiple)
		{
			if (std::get<1>(participant1) == 0 && std::get<1>(participant2) == 0)
			{
				GoToNextStage();
				return;
			}
			else if (std::get<1>(participant1) == 0 && std::get<0>(participant1) == m_duelParticipants[0].GetName())
			{
				StealTerritoryFromDefender();
				GoToNextStage();
				GoToNextStage();
				m_duelParticipants.clear();
			}
		}
		else 
		{
			if (std::get<0>(participant1) == m_duelParticipants[0].GetName())
			{
				StealTerritoryFromDefender();
			}
			GoToNextStage();
			m_duelParticipants.clear();
		}
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
		m_multipleAnswerQuestions = other.m_multipleAnswerQuestions;
		m_numericalAnswerQuestions = other.m_numericalAnswerQuestions;
		numericQuestionIndex = other.numericQuestionIndex;
		multipleQuestionIndex = other.multipleQuestionIndex;
		m_currentStage = other.m_currentStage;
		m_stages = other.m_stages;
		m_chooseTerritoryRoundsNumber = other.m_chooseTerritoryRoundsNumber;
		m_currentStageIndex = other.m_currentStageIndex;
		m_duelRoundsNumber = other.m_duelRoundsNumber;
		m_duelParticipants = other.m_duelParticipants;
		m_playersWhoSentRequest = other.m_playersWhoSentRequest;
		m_choosedTerritoryCounter = other.m_choosedTerritoryCounter;
		m_duelOrder = other.m_duelOrder;
		m_duelOrderIndex = other.m_duelOrderIndex;
	}
	return *this;
}

void Game::Start()
{
	m_currentStage = Stage::NumericalAnswerQuestion;
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

void Game::StealTerritoryFromDefender()
{
	if (m_board[m_attackedPosition].GetScore() == 100)
	{
		m_board[m_attackedPosition].SetOwner(m_duelParticipants[0]);
		if (m_board[m_attackedPosition].GetIsBase())
		{
			//steall all territories()
		}
	}
	else
	{
		m_board[m_attackedPosition].SetScore(m_board[m_attackedPosition].GetScore() - 100);
	}
}

void Game::StealAllTerritories()
{
	uint16_t position = 0;
	for (size_t i = 0; i < m_board.GetHeight(); i++)
	{
		for (size_t j = 0; j < m_board.GetWidth(); j++)
		{
			if (m_board[position].GetOwner().value().GetName() == m_duelParticipants[1].GetName())
			{
				m_board[position].SetOwner(m_duelParticipants[0]);
				position++;
			}
		}
	}
}

void Game::AddPlayerWhoSentRequest(const std::string& playersName)
{
	m_playersWhoSentRequest.insert(playersName);
}

void Game::AddPlayerToDuel(const Player& player)
{
	if (m_duelParticipants.size() > 2)
	{
		throw std::out_of_range("Maximum 2 players can be in a duel");
	}
	else
	{
		m_duelParticipants.emplace_back(player);
	}
}

void Game::SetStagesForChooseBase()
{
	m_stages.push_back(Stage::NumericalAnswerQuestion);
	for (size_t i = 0; i < m_players.size(); i++)
	{
		m_stages.push_back(Stage::ChooseBase);
		m_stages.push_back(Stage::Update);
	}
}

void Game::SetStagesForChooseTerritory()
{
	for (size_t i = 0; i < m_chooseTerritoryRoundsNumber; i++)
	{
		m_stages.push_back(Stage::NumericalAnswerQuestion);
		for (size_t i = 0; i < ((m_players.size() - 1) * m_players.size()) / 2; i++)
		{
			m_stages.push_back(Stage::ChooseTerritory);
			m_stages.push_back(Stage::Update);
		}
	}
	if (m_players.size() == 4)
	{
		for (size_t i = 0; i < 4; i++)
		{
			m_stages.pop_back();
			m_stages.pop_back();
		}
	}
}

void Game::SetStagesForDuel()
{
	for (size_t i = 0; i < m_duelRoundsNumber; i++)
	{
		m_stages.push_back(Stage::Attack);
		m_stages.push_back(Stage::MultipleAnswerQuestion);
		m_stages.push_back(Stage::NumericalAnswerQuestion);
		m_stages.push_back(Stage::Update);
	}
	m_duelOrder = m_players;
	std::random_device rd;
	std::ranges::shuffle(m_duelOrder, rd);
	m_duelOrderIndex = m_duelOrder.size()-1;
}

void Game::ClearPlayersWhoSentRequest()
{
	m_playersWhoSentRequest.clear();
}

void Game::InsertQueueParticipant(const std::string& username, const int& answerCorrentness, const int& responseTime)
{
	Participant participant(username, answerCorrentness, responseTime);
	m_participantsQueue.push(participant);
	if (m_currentStageIndex > 1)
	{
		bool isMultiple;
		if (m_stages[m_currentStageIndex - 1] == Stage::Attack)
		{
			isMultiple = true;
			DetermineDuelSituation(isMultiple);
		}
		else if (m_stages[m_currentStageIndex - 2] == Stage::Attack)
		{
			isMultiple = false;
			DetermineDuelSituation(isMultiple);
		}
		else if (m_participantsQueue.size() == m_players.size())
		{
			GoToNextStage();
		}
	}
	else if (m_participantsQueue.size() == m_players.size())
	{
			GoToNextStage();
	}
}