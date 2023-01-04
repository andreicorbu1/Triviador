#pragma once
#include "Game.h"
#include <crow.h>

struct NumericalAnswerQuestionHandler
{
public:
	explicit NumericalAnswerQuestionHandler(Game& game);
	crow::json::wvalue operator()(const crow::request& req) const;
private:
	Game& m_game;
};