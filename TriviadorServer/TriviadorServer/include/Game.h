#pragma once
#include "Board.h"
#include "QuestionManager.h"
#include "Player.h"
#include <chrono>
#include <algorithm>
#include <ranges>
class Game
{
public:
	enum class Stage : uint16_t
	{
		Stage1,
		Stage2,
		Stage3,
		Stage4
	};

	Game() = default;
	Game(const std::vector<Player>& players);
	Game(const Game& other);
	~Game() = default;

	// Getters:
	Board GetBoard() const;
	std::vector<Player> GetPlayers() const;
	uint16_t GetRounds() const;
	int32_t GetGameID() const;
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
	std::string CurrentStage() const;
	const std::unordered_set<std::string>& GetPlayersWhoSentRequest();
	

	//Setters:
	void SetBoard(const Board& board);
	void SetPlayers(const std::vector<Player>& players);
	void SetRounds(const uint16_t& rounds);
	void SetGameID(const int32_t& gameID);
	void SetQuestions(const uint16_t& numberOfPlayers);
	void GoToNextStage();

	//Operators:
	Game& operator =(const Game& other);

	// Methods:
	void Start();
	void AddToAnswered(int questionId, const Player& player);
	void AddPlayerWhoSentRequest(const std::string& playersName);
private:
	void Cleanup();
	void ChooseBaseTerritories(const std::vector<std::pair<Player, std::pair<int, int>>>& players);
	void ChooseTerritories(const std::vector<std::pair<Player, std::vector<std::pair<int, int>>>>& playersOrder);
	const uint16_t kTwoPlayersNumericAnswerQuestions = 18;
	const uint16_t kTwoPlayersMultipleAnswerQuestions = 10;
	const uint16_t kThreePlayersNumericAnswerQuestions = 17;
	const uint16_t kThreePlayersMultipleAnswerQuestions = 12;
	const uint16_t kFourPlayersNumericAnswerQuestions = 21;
	const uint16_t kFourPlayersMultipleAnswerQuestions = 16;
	static QuestionManager m_questionManager;
private:
	Board m_board;
	std::vector<Player> m_players;
	std::unordered_map<uint16_t, std::vector<Player>> m_alreadyAnswered;
	std::vector<MultipleAnswerQuestion> m_multipleAnswerQuestions;
	std::vector<NumericalAnswerQuestion> m_numericalAnswerQuestions;
	uint16_t m_gameRounds;
	Stage m_currentStage;
	int32_t m_ID;	
	uint16_t numericQuestionIndex = 0;
	uint16_t multipleQuestionIndex = 0;
	std::unordered_set<std::string> m_playersWhoSentRequest;
};

