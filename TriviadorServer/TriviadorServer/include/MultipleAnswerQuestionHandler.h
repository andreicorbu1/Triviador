#pragma once
#include "QuestionManager.h"
#include "Game.h";
#include <crow.h>
struct MultipleAnswerQuestionHandler
{
public:
	explicit MultipleAnswerQuestionHandler(Game& game);
	crow::response operator()(const crow::request& req) const;
private:
	Game& m_game;
};