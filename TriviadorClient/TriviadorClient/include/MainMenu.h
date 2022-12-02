#pragma once

#include <QWidget>
#include "ui_MainMenu.h"
#include "Game.h"
#include "Registration.h"
#include "Player.h"

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(QWidget* parent = nullptr);
    ~MainMenu();

    void hiMessage(const std::string& playerName);


private slots:
    void on_myProfileButton_clicked() const;
    void on_creditsButton_clicked() const;
    void on_logOutButton_clicked();
    void on_playButton_clicked() const;
    void on_createGameButton_clicked() const;
    void on_backButton_clicked();
    void on_twoPlayersButton_clicked();

public slots:
    void Show();


private:
    Ui::MainMenuClass ui;
};
