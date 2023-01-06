#pragma once

#include <QWidget>
#include "ui_MainMenu.h"
#include "Game.h"
#include "Registration.h"
#include <QMessageBox>
#include "Lobby.h"
#include "User.h"

class MainMenu : public QWidget
{
	Q_OBJECT

public:
	MainMenu(QWidget* parent = nullptr);
	MainMenu(const User& user, QWidget* parent = nullptr);
	~MainMenu();

	void hiMessage(const std::string& playerName);
	bool CheckGameCanStart();
	void StartLobby(std::string lobbyID);

public slots:
	void Show();

private slots:
	void on_myProfileButton_clicked() const;
	void on_creditsButton_clicked() const;
	void on_logOutButton_clicked();
	void on_playButton_clicked() const;
	void on_joinButton_clicked() const;
	void on_joinLobbyButton_clicked();
	void on_createButton_clicked();

	void on_lobbyFinished();
	void on_gameFinished();

private:
	Ui::MainMenuClass ui;
	Game* m_game;
	Lobby* m_lobby;
	User m_user;
};
