#include "SendAnswerNumericalQuestion.h"

SendAnswerNumericalQuestion::SendAnswerNumericalQuestion(Game& game) : m_game(game)
{}

crow::response SendAnswerNumericalQuestion::operator()(const crow::request & req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto questionId = bodyArgs.find("id");
	auto answer = bodyArgs.find("answer");
	if (questionId != end && answer != end)
	{
		uint16_t id = std::stoi(questionId->second);
		int ans = std::stoi(answer->second);
		try
		{
			int rightAnswer = m_game.GetNumericalAnswerQuestion(id).GetRightAnswer();
			if (rightAnswer == ans)
			{
				return crow::response(200, "0");
			}
			else
			{
				return crow::response(201, std::to_string(abs(rightAnswer - ans)));
			}
		}
		catch (const std::exception& e)
		{
			return crow::response(401, e.what());
		}
	}
	return crow::response(401, "Question not found");
}
