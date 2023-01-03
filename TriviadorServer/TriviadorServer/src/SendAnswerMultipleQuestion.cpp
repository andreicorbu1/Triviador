#pragma once
#include "SendAnswerMultipleQuestion.h"

SendAnswerMultipleQuestion::SendAnswerMultipleQuestion(Game& game) : m_game(game)
{}

crow::response SendAnswerMultipleQuestion::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto questionId = bodyArgs.find("id");
	auto answer = bodyArgs.find("answer");
	if (questionId != end && answer != end)
	{
		uint16_t id = std::stoi(questionId->second);
		std::string ans = answer->second;
		try
		{
			std::string rightAnswer = m_game.GetMultipleAnswerQuestion(id).GetRightAnswer();
			if (rightAnswer == ans)
			{
				return crow::response(200, "Answer was correct");
			}
			else
			{
				return crow::response(404, "Answer was not correct");
			}
		}
		catch (const std::exception& e)
		{
			return crow::response(401, "Question not found");
		}
	}
	return crow::response(401, "Question not found");
}
