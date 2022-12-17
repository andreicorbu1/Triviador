#include "NumericalAnswerQuestionHandler.h"

NumericalAnswerQuestionHandler::NumericalAnswerQuestionHandler(QuestionManager& questionManager) : m_questionManager(questionManager)
{}

crow::json::wvalue NumericalAnswerQuestionHandler::operator()(const crow::request& req) const
{
	int id = m_questionManager.GetRandomNumericalAnswerQuestionsID();
	NumericalAnswerQuestion numericalAnswerQuestion(m_questionManager.GetNumericalAnswerQuestion(id));
	crow::json::wvalue question
	{
		{"question", numericalAnswerQuestion.GetQuestion()},
		{"right_answer", numericalAnswerQuestion.GetRightAnswer()}
	};
	return crow::json::wvalue(question);
}
