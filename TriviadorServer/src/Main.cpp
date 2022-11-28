#include <filesystem>
#include <iostream>
#include <memory>
#include "User.h"
#include "AccountsManager.h"
#include "MultipleAnswerQuestion.h"
#include "QuestionManager.h"
#include <crow.h>

int main()
{
	MultipleAnswerQuestion maq;
	QuestionStruct<std::string> qs;
	maq.SetID(-1);
	maq.SetQuestion("Ce zici tibi?");
	/*qs.m_id=-1;
	qs.m_question = "Cate puli are tibi in gura?";
	qs.m_rightAnswer = "minim 67";
	qs.m_answer1 = "cel putin una";
	qs.m_answer2 = "nu stiu frate nu ma bag";
	qs.m_answer3 = "ba, are cateva";
	qs.m_answer4 = "pe a mea sigur";*/
	QuestionManager questionManager;
	questionManager.AddQuestion(maq);
	//questionManager.AddQuestion(maq);
	//NumericalAnswerQuestion naq;
	AccountManager userList;
	crow::SimpleApp app;
	CROW_ROUTE(app, "/")([]() {return  "Testing the server"; });
	CROW_ROUTE(app, "/signup")(
		[&userList](const crow::request& req) {
			char* usernameChr = req.url_params.get("username");
			char* passwordChr = req.url_params.get("password");
			std::string password;
			std::string username;
			if (usernameChr != nullptr)
			{
				username = usernameChr;
			}
			else
			{
				return crow::response(400);
			}
			if (passwordChr != nullptr)
			{
				password =  passwordChr;
			}
			else
			{
				return crow::response(400);
			}
			if (userList.SearchUser(username) == true)
			{
				return crow::response(403, "Username-ul introdus este deja existent.");
			}
			User user(username, password);
			userList.AddUser(user);
			if (!userList.SearchUser(username))
			{
				return crow::response(406, "Parola nu a putut fi validata, va rugam sa aveti cel putin o litera mare, un caracter special si cel putin o cifra.");
			}
			return crow::response(200, "V-ati inregistrat cu succes!");
		}
	);
	CROW_ROUTE(app, "/login")(
		[&userList](const crow::request& req) {
			char* usernameChr = req.url_params.get("username");
			char* passwordChr = req.url_params.get("password");
			std::string password;
			std::string username;
			if (usernameChr != nullptr)
			{
				username = usernameChr;
			}
			else
			{
				return crow::response(400);
			}
			if (passwordChr != nullptr)
			{
				password =  passwordChr;
			}
			else
			{
				return crow::response(400);
			}
			if (userList.SearchUser(username) == true)
			{
				User user = userList.GetUser(username);
				if (user.GetPassword() != password)
				{
					return crow::response(401, "Parola introdusa nu este corecta, va rugam reincercati.");
				}
			}
			else 
			{
				return crow::response(406, "Username-ul introdus nu este existent.");
			}
			
			return crow::response(200, "V-ati autentificat cu succes!");
		}
	);

	app.port(18080).multithreaded().run();
	return 0;
}
