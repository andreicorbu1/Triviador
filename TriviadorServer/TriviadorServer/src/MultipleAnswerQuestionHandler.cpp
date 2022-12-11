#include "MultipleAnswerQuestionHandler.h"

MultipleAnswerQuestionHandler::MultipleAnswerQuestionHandler(QuestionManager& questionManager) : m_questionManager(questionManager)
{}

crow::json::wvalue MultipleAnswerQuestionHandler::operator()(const crow::request& req) const
{
	int id = m_questionManager.GetRandomMultipleAnswerQuestionsID();
	MultipleAnswerQuestion multipleAnswerQuestion(m_questionManager.GetMultipleAnswerQuestion(id));
	std::vector<std::string> answers = multipleAnswerQuestion.GetAnswers();
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(answers.begin(), answers.end(), g);

	std::vector <crow::json::wvalue> answersJson;
	for (auto& answer : answers)
	{
		answersJson.push_back(crow::json::wvalue(answer));
	}

	crow::json::wvalue question
	{
		{"question", multipleAnswerQuestion.GetQuestion()},
		{"right_answer", multipleAnswerQuestion.GetRightAnswer()},
		{"answers", answersJson}
	};
	return crow::json::wvalue(question);
}
