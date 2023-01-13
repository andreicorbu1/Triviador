#include "SendAnswerNumericalQuestion.h"

SendAnswerNumericalQuestion::SendAnswerNumericalQuestion(Game& game) : m_game(game)
{}

crow::response SendAnswerNumericalQuestion::operator()(const crow::request& req) const
{
	auto bodyArgs = ParseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameArg = bodyArgs.find("username");
	auto idArg = bodyArgs.find("id");
	auto answerArg = bodyArgs.find("answer");
	auto responseTimeArg = bodyArgs.find("responseTime");
	if (idArg == end || answerArg == end)
		return crow::response(404, "Question not found");

	std::string username = usernameArg->second;
	uint16_t id = std::stoul(idArg->second);
	int answer = std::stoi(answerArg->second);
	int responseTime = std::stoi(responseTimeArg->second);

	try
	{
		int rightAnswer = m_game.GetNumericalAnswerQuestion(id).GetRightAnswer();
		int answerCorrectness = abs(rightAnswer - answer);
		
		m_game.InsertQueueParticipant(username, answerCorrectness, responseTime);
		
		return crow::response(200, std::to_string(answerCorrectness));
	}
	catch (const std::exception& e)
	{
		return crow::response(401, e.what());
	}
}
