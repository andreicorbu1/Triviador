#pragma once
#include "SendAnswerMultipleQuestion.h"

SendAnswerMultipleQuestion::SendAnswerMultipleQuestion(Game& game) : m_game(game)
{}

crow::response SendAnswerMultipleQuestion::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameArg = bodyArgs.find("username");
	auto idArg = bodyArgs.find("id");
	auto answerArg = bodyArgs.find("answer");
	auto responseTimeArg = bodyArgs.find("responseTime");

	if (idArg == end && answerArg == end)
	{
		return crow::response(404, "Question not found");
	}

	std::string username = usernameArg != end ? usernameArg->second : "";
	uint16_t id = std::stoi(idArg->second);
	std::string answer = answerArg->second;
	int responseTime = responseTimeArg != end ? std::stoi(responseTimeArg->second) : 0;
		
	try
	{
		std::string rightAnswer = m_game.GetMultipleAnswerQuestion(id).GetRightAnswer();
		if (rightAnswer == answer)
		{
			return crow::response(200, "Answer was correct");
		}
		else
		{
			return crow::response(200, "Answer was not correct");
		}
	}
	catch (const std::exception& e)
	{
		return crow::response(404, "Question not found");
	}
}