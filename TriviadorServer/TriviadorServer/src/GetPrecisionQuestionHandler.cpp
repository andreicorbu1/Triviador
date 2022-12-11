#include "GetPrecisionQuestionHandler.h"

GetPrecisionQuestionHandler::GetPrecisionQuestionHandler(QuestionManager& questionManager) : m_questionManager(questionManager)
{}

crow::json::wvalue GetPrecisionQuestionHandler::operator()(const crow::request & req) const
{
	int id = m_questionManager.GetRandomMultipleAnswerQuestionsID();
	MultipleAnswerQuestion multipleAnswerQuestion(m_questionManager.GetMultipleAnswerQuestion(id));
	std::vector<std::string>answers = multipleAnswerQuestion.GetAnswers();
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(answers.begin(), answers.end(), g);
	crow::json::wvalue question
	{
		{"question", multipleAnswerQuestion.GetQuestion()},
		{"right_answer", multipleAnswerQuestion.GetRightAnswer()},
		{"answer1", answers[0]},
		{"answer2", answers[1]},
		{"answer3", answers[2]},
		{"answer4", answers[3]}
	};
	return crow::json::wvalue(question);
}
