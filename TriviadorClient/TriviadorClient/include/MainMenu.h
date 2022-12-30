#pragma once

#include <QWidget>
#include "ui_MainMenu.h"
#include "Game.h"
#include "Registration.h"
#include <QMessageBox>
#include "Lobby.h"


class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(QWidget* parent = nullptr);
    ~MainMenu();

    void hiMessage(const std::string& playerName);
    void StartGame(std::vector<Player>& players);
    void StartLobby();

public slots:
    void Show();

private slots:
    void on_myProfileButton_clicked() const;
    void on_creditsButton_clicked() const;
    void on_logOutButton_clicked();
    void on_playButton_clicked() const;
    void on_joinGameButton_clicked() const;
    void on_joinLobbyButton_clicked();
    void on_createGameButton_clicked() const;
    void on_backButton_clicked();
    void on_twoPlayersButton_clicked();
    void on_threePlayersButton_clicked();
    void on_fourPlayersButton_clicked();

    void on_gameFinished();

private:
    void WaitingInLobby(std::string lobbyID) const;

private:
    Ui::MainMenuClass ui;
    Game* m_game;
    Lobby* m_lobby;
};
