#pragma once

#include <QWidget>
#include "ui_MainMenu.h"
#include "Game.h"
#include "Registration.h"

class MainMenu : public QWidget
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = nullptr);
	~MainMenu();

void hiMessage(const std::string& playerName);


private slots:
	void on_mainButton_clicked() const;
	void on_myProfileButton_clicked() const;
	void on_creditsButton_clicked() const;
	void on_logOutButton_clicked();
	void on_playButton_clicked();

public slots:
	void ShowMenu();


private:
	Ui::MainMenuClass ui;
};
