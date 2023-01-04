#pragma once
#include "QuestionManager.h"
#include "Game.h";
#include <crow.h>
struct MultipleAnswerQuestionHandler
{
public:
	explicit MultipleAnswerQuestionHandler(Game& game);
	crow::json::wvalue operator()(const crow::request& req) const;
private:
	Game& m_game;
};