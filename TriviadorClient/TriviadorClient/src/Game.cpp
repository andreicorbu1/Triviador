#include "Game.h"

Game::Game(QWidget* mainMenu)
    : m_mainMenu(mainMenu)
    , m_questionManager(new QuestionManager(this))
{
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    ui.setupUi(this);
    m_mainMenu->hide();
    m_questionManager->ShowMultipleAnswerQuestion();
    m_questionManager->ShowMultipleAnswerQuestion();
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
