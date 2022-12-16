#include "Game.h"

Game::Game(QWidget* mainMenu)
	: m_questionWindow(QuestionWindow(this))
	, m_board(Board(1, 1))
{
	setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	ui.setupUi(this);
	SetBackground();
}

Game::Game(std::vector<Player>& players, QWidget* parent)
	: m_questionWindow(QuestionWindow(this))
	, m_players(players)
{
	setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	ui.setupUi(this);
	SetBackground();
	
	switch (m_players.size())
	{
	case 2:
		m_board = Board(3, 3);
		m_rounds = 5;
		break;
	case 3:
		m_board = Board(5, 3);
		m_rounds = 4;
		break;
	case 4:
		m_board = Board(4, 6);
		m_rounds = 3;
		break;
	default:
		break;
	}
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
	emit finished();
}
