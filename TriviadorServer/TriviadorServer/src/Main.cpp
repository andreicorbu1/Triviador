#include "AddToAcountListHandler.h"
#include "LoginHandler.h"
#include "MultipleAnswerQuestion.h"
#include "QuestionManager.h"

#include <crow.h>

int main()
{
	QuestionManager questionManager("resource/Questions.sqlite");
	questionManager.PopulateStorage();

	AccountManager userList("resource/Accounts.sqlite");
	crow::SimpleApp app;

	//register route
	auto& addUserToAccountList = CROW_ROUTE(app, "/signup").methods(crow::HTTPMethod::PUT);
	addUserToAccountList(AddAccountHandler(userList));

	//login route
	auto& loginToAccount = CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::POST);
	loginToAccount(LoginHandler(userList));

	CROW_ROUTE(app, "/multipleAnswerQuestion")([&questionManager]()
	{
			MultipleAnswerQuestion multipleAnswerQuestion = questionManager.GetRandomMultipleAnswerQuestion();
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
	});

	app.port(18080).multithreaded().run();
	return 0;
}
