#include "Game.h"
#include <crow.h>
#include "utils.h"

struct SendAnswerMultipleQuestion
{
	SendAnswerMultipleQuestion(Game& game);
	crow::response operator()(const crow::request& req) const;
private:
	Game& m_game;
};