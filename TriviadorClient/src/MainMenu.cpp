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
	QString message = "Salut, " + QString::fromStdString(playerName);
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

void MainMenu::on_logOutButton_clicked() const
{
	qDebug() << "Log Out button clicked";
}
