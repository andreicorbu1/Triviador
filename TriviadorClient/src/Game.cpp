#include "Game.h"

Game::Game()
{
	ui.setupUi(this);
	MainMenu* mainMenu = new MainMenu;
	connect(ui.exitButton, &QPushButton::clicked, mainMenu, &MainMenu::showMaximized);
}

Game::~Game()
{
    // empty
}

void Game::on_exitButton_clicked() 
{
	close();
	//emit notifyExitButtonClicked();
}
