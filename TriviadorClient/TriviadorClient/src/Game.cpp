#include "Game.h"

#include <QTimer>

Game::Game(QWidget* mainMenu)
    : m_mainMenu(mainMenu)
{
    ui.setupUi(this);
    m_mainMenu->hide();

    m_question = new Question(this);
    m_question->show();
    
    // TEST
    QTimer::singleShot(3000, m_question, &Question::hide);
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
