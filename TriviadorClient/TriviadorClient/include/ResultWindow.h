#pragma once

#include <QWidget>
#include <QPainter>
#include "ui_ResultWindow.h"

#include <algorithm>
#include "Player.h"

class ResultWindow : public QWidget
{
	Q_OBJECT

public:
	ResultWindow(QWidget *parent = nullptr);
	ResultWindow(std::vector<Player>& players, QWidget* parent = nullptr);
	~ResultWindow();
	
	void paintEvent(QPaintEvent* paintEvent);

signals:
	void backToMenu();

private slots:
	void on_backToMenuButton_clicked();

private:
	const std::pair<uint16_t, uint16_t> playersTableSize = { 400, 75 };
	const std::pair<uint16_t, uint16_t> playersTableStartPoint = { 200, 95 };
	
private:
	Ui::ResultWindowClass ui;
	
	std::vector<Player> m_players;
};
