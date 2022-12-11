#include "Game.h"

Game::Game(QWidget* mainMenu)
	: m_mainMenu(mainMenu)
	, m_board(1, 1)
  , m_questionWindow(QuestionWindow(this))
{
	setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	ui.setupUi(this);
	m_mainMenu->hide();
	ShowQuestion(QuestionType::MultipleAnswer);
}

Game::Game(const Player& player1, const Player& player2, QWidget* mainMenu)
	: m_mainMenu(mainMenu)
	, m_board(3, 3)
	, m_players{ player1, player2 }
	, m_gameRounds(5)
  , m_questionWindow(QuestionWindow(this))
{
	ui.setupUi(this);
	m_mainMenu->hide();
	SetBackground();
	//ShowQuestion(QuestionType::MultipleAnswer);
}

Game::Game(const Player& player1, const Player& player2, const Player& player3, QWidget* mainMenu)
	: m_mainMenu(mainMenu)
	, m_board(5, 3)
	, m_players{ player1, player2, player3 }
	, m_gameRounds(4)
  , m_questionWindow(QuestionWindow(this))
{
	ui.setupUi(this);
	SetBackground();
	m_mainMenu->hide();
	//ShowQuestion(QuestionType::MultipleAnswer);
}

Game::Game(const Player& player1, const Player& player2, const Player& player3, const Player& player4, QWidget* mainMenu)
	: m_mainMenu(mainMenu)
	, m_board(4, 6)
	, m_players{ player1, player2, player3, player4 }
	, m_gameRounds(4)
  , m_questionWindow(QuestionWindow(this))
{
	ui.setupUi(this);
	SetBackground();
	m_board.SetMasksForFourPlayersGame();
	m_mainMenu->hide();
	//ShowQuestion(QuestionType::NumericalAnswer);
}

Game::~Game()
{
	// empty
}

void Game::ShowQuestion(QuestionType type)
{
    m_questionWindow.SetQuestionType(type);
    m_questionWindow.FetchQuestion();
    m_questionWindow.Show();
}

void Game::SetBackground()
{
	if (!m_background.load("../TriviadorClient/resource/Background.png"))
	{
		throw "The background couldn't load!";
	}
	QSize screenSize = qApp->screens()[0]->size();
	m_background = m_background.scaled(screenSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}


void Game::paintEvent(QPaintEvent* paintEvent)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, m_background);
	//m_board.PrintBoard(this);
}

void Game::on_exitButton_clicked()
{
	close();
	m_mainMenu->showMaximized();
}
