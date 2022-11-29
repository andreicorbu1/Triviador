#include "Game.h"

Game::Game(QWidget* mainMenu)
    : m_mainMenu(mainMenu)
{
    ui.setupUi(this);
    m_mainMenu->hide();
}

Game::~Game()
{
    // empty
}

void Game::on_exitButton_clicked()
{
    close();
    m_mainMenu->showMaximized();
}
