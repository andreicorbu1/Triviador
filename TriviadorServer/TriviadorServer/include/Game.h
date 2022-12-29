#pragma once
#include "Board.h"
#include "QuestionManager.h"
#include "Player.h"
#include <algorithm>
#include <ranges>
class Game
{
public:
	Game(const Player& player1, const Player& player2);
	Game(const Player& player1, const Player& player2, const Player& player3);
	Game(const Player& player1, const Player& player2, const Player& player3, const Player& player4);
	Game(const Game& other);
	~Game() = default;

	// Getters:
	Board GetBoard() const;
	std::vector<Player> GetPlayers() const;
	int GetRounds() const;
	int32_t GetGameID() const;
	Player GetWinner();
	NumericalAnswerQuestion GetNumericalAnswerQuestion();
	MultipleAnswerQuestion GetMultipleAnswerQuestion();

	//Setters:
	void SetBoard(const Board& board);
	void SetPlayers(const std::vector<Player>& players);
	void SetRounds(const int& rounds);
	void SetGameID(const int32_t& gameID);

	//Operators:
	Game& operator =(const Game& other);

	// Methods:
	void Start();

private:
	void Cleanup();
	void ChooseBaseTerritories();
	const uint16_t kTwoPlayersNumericAnswerQuestions = 18;
	const uint16_t kTwoPlayersMultipleAnswerQuestions = 10;
	const uint16_t kThreePlayersNumericAnswerQuestions = 17;
	const uint16_t kThreePlayersMultipleAnswerQuestions = 12;
	const uint16_t kFourPlayersNumericAnswerQuestions = 21;
	const uint16_t kFourPlayersMultipleAnswerQuestions = 16;
	uint16_t numericQuestionIndex = 0;
	uint16_t multipleQuestionIndex = 0;
	static QuestionManager m_questionManager;
private:
	Board m_board;
	std::vector<Player> m_players;
	std::vector<MultipleAnswerQuestion> m_multipleAnswerQuestions;
	std::vector<NumericalAnswerQuestion> m_numericalAnswerQuestions;
	int m_gameRounds;
	int32_t m_ID;
};

