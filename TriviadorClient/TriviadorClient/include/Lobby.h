#pragma once

#include <QWidget>
#include "ui_Lobby.h"
#include <QPainter>

class Lobby : public QWidget
{
	Q_OBJECT

public:
	Lobby(QWidget *parent = nullptr);
	~Lobby();

private:
	void paintEvent(QPaintEvent* paintEvent);

private:
	Ui::LobbyClass ui;
};
