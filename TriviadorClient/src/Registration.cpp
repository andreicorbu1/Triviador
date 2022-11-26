#include "Registration.h"

Registration::Registration(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

Registration::~Registration()
{
}

void Registration::on_logInButton_clicked() const
{
    qDebug() << "Log in button clicked";
    
}

void Registration::on_signUpButton_clicked() const
{
    qDebug() << "Sign up button clicked";
}

//bool Registration::IsValidUsername(const std::string& username)
//{
//    return username.length() >= 3 && username.length() <= 10;
//}
//
//bool Registration::IsValidPassword(const std::string& password)
//{
//    return password.length() >= 8 && password.length() <= 20;
//}
