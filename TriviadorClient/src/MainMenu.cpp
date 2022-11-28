#include "MainMenu.h"

MainMenu::MainMenu(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

MainMenu::~MainMenu()
{}

void MainMenu::hiMessage(const std::string& playerName)
{
	QString message = "Salut, ";
    message += playerName.c_str();
	ui.hiMessage->setText(message);
}

void MainMenu::on_mainButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.main);
}

void MainMenu::on_myProfileButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.myProfile);
}

void MainMenu::on_creditsButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.credits);
}



void MainMenu::on_playButton_clicked() 
{
	Game *game = new Game;
	close();
	game->showMaximized();
}

void MainMenu::ShowMenu()
{
	showMaximized();
}

void MainMenu::on_logOutButton_clicked()
{
    close();
    Registration* registration = new Registration;
    registration->show();
    
	qDebug() << "Log Out button clicked";
}
