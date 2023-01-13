#pragma once

#include <QWidget>
#include <QTimer>
#include "ui_Lobby.h"
#include <QPaintEvent>
#include <QPainter>
#include <QMessageBox>
#include <string>
#include <crow.h>
#include <cpr/cpr.h>
#include "../../DLL/User.h"
#include <Player.h>
#include "Game.h"

class Lobby : public QWidget
{
	Q_OBJECT

public:
	Lobby(const std::string& lobbyID, const std::string& username, QWidget* parent = nullptr);
	~Lobby();
	void closeEvent(QCloseEvent* event) override;

signals:
	void finished();

private slots:
	void on_leaveLobbyButton_clicked();
	void on_startGameButton_clicked();
	void on_gameFinished();
	void LobbyLoop();

private:
	void HideAllPlayersName();
	void SetPlayersLabel();
	void StartGame();

	std::string m_lobbyID;

private:
	Ui::LobbyClass ui;
	Player m_currentPlayer;
	std::vector<Player> m_players;
	std::vector<QLabel*> m_playersLabel;
	Game* m_game;
};
