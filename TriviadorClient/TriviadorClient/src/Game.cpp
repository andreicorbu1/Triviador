#include "Game.h"

Game::Game(QWidget* mainMenu)
    : m_mainMenu(mainMenu)
    , m_board(1,1)
{
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    ui.setupUi(this);
    m_mainMenu->hide();

    m_question = new Question(this);
    m_question->show();
}

Game::Game(const Player& player1, const Player& player2, QWidget* mainMenu)
    : m_mainMenu(mainMenu)
    , m_board(3, 3)
    , m_players{ player1, player2 }
    , m_gameRounds(5)

{
    ui.setupUi(this);
    m_pixmap.load("../TriviadorClient/resource/testMap.png");
    m_pixmap = m_pixmap.scaled(600, 600);
    m_mainMenu->hide();
}

Game::Game(const Player& player1, const Player& player2, const Player& player3, QWidget* mainMenu)
    : m_mainMenu(mainMenu)
    , m_board(5, 3)
    , m_players{ player1, player2, player3 }
    , m_gameRounds(4)

{
    ui.setupUi(this);
    m_mainMenu->hide();
}

Game::Game(const Player& player1, const Player& player2, const Player& player3, const Player& player4, QWidget* mainMenu)
    : m_mainMenu(mainMenu)
    , m_board(6, 4)
    , m_players{ player1, player2, player3, player4 }
    , m_gameRounds(4)
{
    ui.setupUi(this);
    m_mainMenu->hide();
}

Game::~Game()
{
    // empty
}

void Game::paintEvent(QPaintEvent* paintEvent)
{
    QPainter painter(this);
    painter.drawPixmap(325, 100, m_pixmap);
    m_board.PrintBoard(this);
}


void Game::on_exitButton_clicked()
{
    close();
    m_mainMenu->showMaximized();
    //m_question->hide();
}
