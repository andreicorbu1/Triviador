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
	m_board.SetCoordinatesAndSize(xPosition, yPosition, rectangularSize);
	m_pixmap.load("../TriviadorClient/resource/testMap.png");
	m_pixmap = m_pixmap.scaled(rectangularSize * 3, rectangularSize * 3);
	m_mainMenu->hide();

	//NumericalAnswerQuestion naq;
	//m_questionWindow.SetQuestion(naq.GetQuestion());	
	ShowQuestion(QuestionType::MultipleAnswer);
}

Game::Game(const Player& player1, const Player& player2, const Player& player3, QWidget* mainMenu)
	: m_mainMenu(mainMenu)
	, m_board(5, 3)
	, m_players{ player1, player2, player3 }
	, m_gameRounds(4)
  , m_questionWindow(QuestionWindow(this))
{
	ui.setupUi(this);
	m_board.SetCoordinatesAndSize(xPosition, yPosition, rectangularSize);
	m_pixmap.load("../TriviadorClient/resource/testMap.png");
	m_pixmap = m_pixmap.scaled(rectangularSize * 5, rectangularSize * 3);
	m_mainMenu->hide();
	ShowQuestion(QuestionType::MultipleAnswer);
}

Game::Game(const Player& player1, const Player& player2, const Player& player3, const Player& player4, QWidget* mainMenu)
	: m_mainMenu(mainMenu)
	, m_board(6, 4)
	, m_players{ player1, player2, player3, player4 }
	, m_gameRounds(4)
  , m_questionWindow(QuestionWindow(this))
{
	ui.setupUi(this);
	m_board.SetCoordinatesAndSize(xPosition, yPosition, rectangularSize-25);
	m_pixmap.load("../TriviadorClient/resource/testMap.png");
	m_pixmap = m_pixmap.scaled((rectangularSize-25) * 6, (rectangularSize-25) * 4);
	m_mainMenu->hide();
	ShowQuestion(QuestionType::NumericalAnswer);
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

void Game::paintEvent(QPaintEvent* paintEvent)
{
	QPainter painter(this);
	painter.drawPixmap(xPosition, yPosition, m_pixmap);
	m_board.PrintBoard(this);
}

void Game::on_exitButton_clicked()
{
	close();
	m_mainMenu->showMaximized();
}
