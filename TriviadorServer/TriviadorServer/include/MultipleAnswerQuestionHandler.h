#pragma once
#include "QuestionManager.h"
#include "Game.h";
#include <crow.h>
struct MultipleAnswerQuestionHandler
{
public:
	explicit MultipleAnswerQuestionHandler(Game& game);
	crow::json::wvalue to_json();
	crow::response operator()(const crow::request& req) const;
private:
	Game& m_game;
};