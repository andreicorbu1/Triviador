#pragma once
#include "Board.h"
#include "QuestionManager.h"
#include "Player.h"
#include "AccountsManager.h"
#include <chrono>
#include <algorithm>
#include <ranges>
#include <queue>
#include <tuple>

using Participant = std::tuple<std::string, int, int>;

class ParticipantCompare
{
public:
	bool operator() (const Participant& firstParticipant, const Participant& secondParticipant) const
	{
		return std::tie(std::get<1>(firstParticipant), std::get<2>(firstParticipant), std::get<0>(firstParticipant)) > std::tie(std::get<1>(secondParticipant), std::get<2>(secondParticipant), std::get<0>(secondParticipant));
	}
};

class Game
{
public:
	enum class Stage : uint16_t
	{
		NumericalAnswerQuestion,
		MultipleAnswerQuestion,
		ChooseBase,
		ChooseTerritory,
		Attack,
		Wait,
		Update,
		Result
	};

	Game() = default;
	Game(const std::vector<Player>& players);
	Game(const Game& other);
	~Game() = default;

	// Getters:
	Board GetBoard() const;
	std::vector<Player> GetPlayers() const;
	std::vector<Player>& GetPlayers();

	Player GetWinner();
	uint16_t GetCurrentNumericalAnswerQuestionIndex() const;
	uint16_t GetCurrentMultipleAnswerQuestionIndex() const;
	std::pair<NumericalAnswerQuestion, uint16_t> GetNumericalAnswerQuestion();
	NumericalAnswerQuestion GetNumericalAnswerQuestion(uint16_t index) const;
	std::pair<NumericalAnswerQuestion, uint16_t> GetNewNumericalAnswerQuestion();
	NumericalAnswerQuestion GetCurrentNumericalAnswerQuestion() const;
	std::pair < MultipleAnswerQuestion, uint16_t> GetMultipleAnswerQuestion();
	std::pair < MultipleAnswerQuestion, uint16_t> GetNewMultipleAnswerQuestion();
	MultipleAnswerQuestion GetCurrentMultipleAnswerQuestion();
	MultipleAnswerQuestion GetMultipleAnswerQuestion(uint16_t index) const;
	size_t GetNumberOfPlayers() const;
	std::string GetCurrentStage() const;
	const std::unordered_set<std::string>& GetPlayersWhoSentRequest() const;
	const std::vector<Player>& GetParticipants() const;
	std::string GetPlayerWhoWillMakeAChoice() const;
	const Player& GetCurrentAttacker();
	uint16_t GetParticipantsQueueSize() const;

	void IncrementNumericalAnswerQuestionIndex();
	void IncrementMultipleAnswerQuestionIndex();

	//Setters:
	void SetBoard(const Board& board);
	void SetPlayers(const std::vector<Player>& players);
	void SetQuestions(const uint16_t& numberOfPlayers);
	void GoToNextStage();
	void AddNullPlayer();
	void SetAttackedPosition(uint16_t position);

	//Operators:
	Game& operator =(const Game& other);

	// Methods:
	void Start();
	void AddToAnswered(int questionId, const Player& player);
	void AddPlayerWhoSentRequest(const std::string& playersName);
	void AddPlayerToDuel(const Player& player);
	void SetStagesForChooseBase();
	void SetStagesForChooseTerritory();
	void SetStagesForDuel();
	void ClearPlayersWhoSentRequest();
	void InsertQueueParticipant(const std::string& username, const int& answerCorrentness, const int& responseTime = 0);
	bool AddTerritory(std::string username, int position, bool isBase);
	bool PopPlayerWhoWillMakeAChoose();
	void DetermineDuelSituation(bool isMultiple=true);
	void DetermineScoreForAllPlayers();
	void UpdateGameHistory(const std::string& username);
	void ClearDuelParticipants();

private:
	void Cleanup();
	void StealTerritoryFromDefender();
	void StealAllTerritories();
	void ClearPlayersScore();
	const uint16_t kTwoPlayersNumericAnswerQuestions = 18;
	const uint16_t kTwoPlayersMultipleAnswerQuestions = 10;
	const uint16_t kThreePlayersNumericAnswerQuestions = 17;
	const uint16_t kThreePlayersMultipleAnswerQuestions = 12;
	const uint16_t kFourPlayersNumericAnswerQuestions = 21;
	const uint16_t kFourPlayersMultipleAnswerQuestions = 20;
	uint16_t m_chooseTerritoryRoundsNumber;
	uint16_t m_duelRoundsNumber;
	static QuestionManager m_questionManager;
	
private:
	Board m_board;
	std::vector<Player> m_players;
	std::vector<Player> m_duelOrder;
	int16_t m_duelOrderIndex;
	std::unordered_map<uint16_t, std::vector<Player>> m_alreadyAnswered;
	std::vector<MultipleAnswerQuestion> m_multipleAnswerQuestions;
	std::vector<NumericalAnswerQuestion> m_numericalAnswerQuestions;
	Stage m_currentStage;
	uint16_t m_currentStageIndex;
	std::vector<Stage>m_stages;
	uint16_t numericQuestionIndex = 0;
	uint16_t multipleQuestionIndex = 0;
	std::unordered_set<std::string> m_playersWhoSentRequest;
	std::vector<Player> m_duelParticipants;
	std::priority_queue<Participant, std::vector<Participant>, ParticipantCompare> m_participantsQueue;
	uint16_t m_choosedTerritoryCounter=0;
	uint16_t m_attackedPosition;
};