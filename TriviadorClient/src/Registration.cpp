#include "Registration.h"

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
    std::string username = ui.usernameInput->text().toUtf8().constData();
    std::string password = ui.passwordInput->text().toUtf8().constData();

    if (!ValidateCredentials(username, password)) return;
    
    cpr::Response res = cpr::Get(cpr::Url{ "http://localhost:18080/login" }, cpr::Parameters{ {"username", username}, {"password", password} });
    
    if (res.status_code == 200)
    {
        close();
        MainMenu* mainMenu = new MainMenu;
        mainMenu->hiMessage(username);
        mainMenu->showMaximized();
    }

    qDebug() << "Log in button clicked";
}

void Registration::on_signUpButton_clicked()
{
    std::string username = ui.usernameInput->text().toUtf8().constData();
    std::string password = ui.passwordInput->text().toUtf8().constData();

    if (!ValidateCredentials(username, password)) return;

    cpr::Response res = cpr::Get(cpr::Url{ "http://localhost:18080/signup" }, cpr::Parameters{ {"username", username}, {"password", password} });

    if (res.status_code == 200)
    {
        close();
        MainMenu* mainMenu = new MainMenu;
        mainMenu->hiMessage(username);
        mainMenu->showMaximized();
    }
    
    qDebug() << "Sign up button clicked";
}

bool Registration::IsValidUsername(const std::string& username) const
{
    return username.length() >= 3 && username.length() <= 10;
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
