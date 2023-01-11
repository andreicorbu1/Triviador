#pragma once
#include "QuestionManager.h"
#include "Game.h";
#include <crow.h>
struct MultipleAnswerQuestionHandler
{
public:
	explicit MultipleAnswerQuestionHandler(Game& game);
	crow::json::wvalue ToJson(const MultipleAnswerQuestion& question, const crow::json::wvalue& players, const crow::json::wvalue& answers, int id) const;
	crow::response operator()(const crow::request& req) const;
private:
	Game& m_game;
};