#pragma once
#include "QuestionManager.h"
#include <crow.h>
struct GetPrecisionQuestionHandler
{
	GetPrecisionQuestionHandler(QuestionManager& questionManager);
	crow::json::wvalue operator()(const crow::request& req) const;
private:
	QuestionManager& m_questionManager;
};