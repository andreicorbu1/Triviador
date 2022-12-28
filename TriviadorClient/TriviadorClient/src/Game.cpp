#include "Game.h"

Game::Game(QWidget* mainMenu)
	: m_questionWindow(QuestionWindow(this))
	, m_board(Board(1, 1))
{
	setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	ui.setupUi(this);
}

Game::Game(std::vector<Player>& players, QWidget* parent)
	: m_questionWindow(QuestionWindow(this))
	, m_players(players)
{
	setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	ui.setupUi(this);

	switch (m_players.size())
	{
	case 2:
		m_board = Board(3, 3, this);
		m_rounds = 5;
		m_board.Set2PGame();
		break;
	case 3:
		m_board = Board(5, 3, this);
		m_rounds = 4;
		m_board.Set3PGame();
		break;
	case 4:
		m_board = Board(4, 6, this);
		m_rounds = 3;
		m_board.Set4PGame();
		break;
	default:
		break;
	}
	ConnectButtons();
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

void Game::LoadBackgroundImage()
{
	if (!m_background.load("../TriviadorClient/resource/Background.png"))
	{
		throw "The background couldn't load!";
	}
}

void Game::ConnectButtons()
{
	for (int i = 0; i < m_board.Size(); i++)
	{
		connect(m_board[i].getButton(), SIGNAL(clicked()), this, SLOT(action()));
	}
}

void Game::action()
{
	qDebug() << "Button clicked!";
}

void Game::paintEvent(QPaintEvent* paintEvent)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, m_background);
}

void Game::resizeEvent(QResizeEvent* event)
{
	this->QWidget::resizeEvent(event);
	LoadBackgroundImage();
	m_background = m_background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

void Game::on_exitButton_clicked()
{
	emit finished();
}
