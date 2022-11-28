#pragma once
#include <qmainwindow.h>
#include "ui_Game.h"
#include "MainMenu.h"
#include "Registration.h"

class Game : public QMainWindow
{
	Q_OBJECT
public:
	Game();
	~Game();

private slots:
	void on_exitButton_clicked();

//signals:
//	void notifyExitButtonClicked() const;


private:
	Ui::MainWindow ui;
};
