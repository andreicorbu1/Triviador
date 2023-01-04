#include "Game.h"
#include <crow.h>
#include "utils.h"

struct SendAnswerNumericalQuestion
{
public:
	SendAnswerNumericalQuestion(Game& game);
	crow::response operator()(const crow::request& req) const;

private:
	Game& m_game;
};