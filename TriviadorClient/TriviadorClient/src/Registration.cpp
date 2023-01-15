#include "Registration.h"
#include <iostream>
#include <string>
Registration::Registration(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Registration::~Registration()
{
	// empty
}

void Registration::on_logInButton_clicked()
{
	ui.errorLabel->setText("");
	std::string username = ui.usernameInput->text().toUtf8().constData();
	std::string password = ui.passwordInput->text().toUtf8().constData();

	if (!ValidateCredentials(username, password))
	{
		ui.errorLabel->setText("Error: Invalid username or password");
		return;
	}

	auto res = cpr::Post(
		cpr::Url{ "http://25.65.182.120:18080/login" },
		cpr::Body{ "username=" + username + "&password=" + password }
	);

	if (res.error.code != cpr::ErrorCode::OK) {
		ui.errorLabel->setText("Error: Couldn't connect to the server");
		return;
	}

	if (res.status_code == 200)
	{
		close();
		MainMenu* mainMenu = new MainMenu(User(username));
		mainMenu->HiMessage(username);
		mainMenu->showMaximized();
	}
	else
	{
		ui.errorLabel->setText("Error: Username or password doesn't match");
	}
}

void Registration::on_signUpButton_clicked()
{
	ui.errorLabel->setText("");
	std::string username = ui.usernameInput->text().toUtf8().constData();
	std::string password = ui.passwordInput->text().toUtf8().constData();

	if (!ValidateCredentials(username, password)) {
		ui.errorLabel->setText("Error: Invalid username or password");
		return;
	}

	auto res = cpr::Put(
		cpr::Url{ "http://25.65.182.120:18080/signup" },
		cpr::Body{ "username=" + username + "&password=" + password }
	);

	if (res.error.code != cpr::ErrorCode::OK) {
		ui.errorLabel->setText("Error: Couldn't connect to the server");
		return;
	}

	if (res.status_code == 201)
	{
		close();
		MainMenu* mainMenu = new MainMenu(User(username));
		mainMenu->HiMessage(username);
		mainMenu->showMaximized();
	}
	else {
		ui.errorLabel->setText("Error: Username already exists");
		qDebug() << res.text.c_str() << "\n";
	}
}

bool Registration::IsValidUsername(const std::string& username) const
{
	return username.length() >= 3 && username.length() <= 20;
}

bool Registration::IsValidPassword(const std::string& password) const
{
	std::regex passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,25}$");
	return std::regex_match(password, passwordRegex);
}

bool Registration::ValidateCredentials(const std::string& username, const std::string& password) const
{
	bool isValidUsername = IsValidUsername(username);
	bool isValidPassword = IsValidPassword(password);

	if (isValidUsername)
	{
		ui.usernameInput->setStyleSheet("border: 2px solid #FCF321");
	}
	else {
		ui.usernameInput->setStyleSheet("border: 2px solid #9B1212");
	}

	if (isValidPassword)
	{
		ui.passwordInput->setStyleSheet("border: 2px solid #FCF321");
	}
	else {
		ui.passwordInput->setStyleSheet("border: 2px solid #9B1212");
	}

	return isValidUsername && isValidPassword;
}