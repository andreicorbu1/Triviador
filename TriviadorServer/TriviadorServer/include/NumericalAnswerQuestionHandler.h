#pragma once
#include "Game.h"
#include <crow.h>

struct NumericalAnswerQuestionHandler
{
public:
	explicit NumericalAnswerQuestionHandler(Game& game);
	crow::json::wvalue to_json(const NumericalAnswerQuestion& question, const crow::json::wvalue& playersJson, uint16_t id) const;
	crow::response operator()(const crow::request& req) const;
private:
	Game& m_game;
};