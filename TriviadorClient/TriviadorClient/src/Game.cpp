#include "Game.h"

Game::Game(QWidget* mainMenu)
    : m_mainMenu(mainMenu)
    , m_questionWindow(QuestionWindow(this))
{
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    ui.setupUi(this);
    m_mainMenu->hide();
    ShowQuestion(QuestionType::MultipleAnswer);
}

Game::~Game()
{
    // empty
}

void Game::ShowQuestion(QuestionType type)
{
    m_questionWindow.SetQuestionType(type);
    m_questionWindow.show();
    m_questionWindow.StartTimer();
}

void Game::on_exitButton_clicked()
{
    close();
    m_mainMenu->showMaximized();
}
