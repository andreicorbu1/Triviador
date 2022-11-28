#pragma once

#include <QWidget>
#include <regex>
#include <cpr/cpr.h>

#include "ui_Registration.h"
#include "MainMenu.h"

class Registration : public QWidget
{
    Q_OBJECT

public:
    Registration(QWidget *parent = nullptr);
    ~Registration();
    
private slots:
    void on_logInButton_clicked();
    void on_signUpButton_clicked();

private:
    bool IsValidUsername(const std::string& username) const;
    bool IsValidPassword(const std::string& password) const;
    bool ValidateCredentials(const std::string& username, const std::string& password) const;

private:
    Ui::RegistrationClass ui;
};
