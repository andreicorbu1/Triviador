#pragma once
#include "qmainwindow.h"
#include "ui_Menu.h"

class Menu:public QMainWindow
{
public:
	Menu();

	void hiMessage(std::string playerName);
private:
	Ui::MainWindow ui;

};
