#pragma once

#include <QWidget>
#include "ui_Lobby.h"
#include <QPaintEvent>
#include <QPainter>
#include <QMessageBox>
#include <string>
#include <cpr/cpr.h>

class Lobby : public QWidget
{
	Q_OBJECT

public:
	Lobby(std::string lobbyID, QWidget *parent = nullptr);
	~Lobby();

signals:
	void finished();

private slots:
	void on_leaveLobbyButton_clicked();

private:
	void paintEvent(QPaintEvent* paintEvent);
	std::string m_lobbyID;

private:
	Ui::LobbyClass ui;
};
