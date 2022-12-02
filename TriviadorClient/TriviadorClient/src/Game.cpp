#include "Game.h"

Game::Game(QWidget* mainMenu)
    : m_mainMenu(mainMenu)
{
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    ui.setupUi(this);
    m_mainMenu->hide();

    m_question = new Question(this);
    m_question->show();
}

Game::~Game()
{
    // empty
}

void Game::on_exitButton_clicked()
{
    close();
    m_mainMenu->showMaximized();
    m_question->hide();
}
