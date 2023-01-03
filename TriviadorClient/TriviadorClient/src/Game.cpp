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
	m_signalMapper = new QSignalMapper(this);

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
		m_board = Board(6, 4, this);
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

void Game::SetBackground()
{
	if (!m_background.load("../TriviadorClient/resource/Background.png"))
	{
		throw "The background couldn't load!";
	}
	m_background = m_background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

void Game::ConnectButtons()
{
	QObject::connect(m_signalMapper, SIGNAL(mappedInt(int)), this, SLOT(action(int)));
	for (int i = 0; i < m_board.Size(); i++)
	{
		//QObject::connect(m_board[i].getButton(), SIGNAL(clicked()), this, SLOT(action(int)));
		QObject::connect(m_board[i].getButton(), SIGNAL(clicked()), m_signalMapper, SLOT(map()));
		m_signalMapper->setMapping(m_board[i].getButton(), i);
	}
}

void Game::action(int position)
{
	qDebug() << "The Button " << position << " was clicked!";
}

void Game::paintEvent(QPaintEvent* paintEvent)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, m_background);
	painter.setBrush(QColor(83, 66, 50));
	for (size_t i = 0; i < m_players.size(); i++)
	{
		QString color = m_players[i].GetColor().c_str();
		QRect playerTable(playersTableStartPoint.first, playersTableStartPoint.second + (i * playersTableSize.second), playersTableSize.first, playersTableSize.second);
		painter.setPen(Qt::black);
		painter.drawRect(playerTable);
		QString tableText = (m_players[i].GetName() + " " + std::to_string(m_players[i].GetScore())).c_str();
		painter.setFont(QFont("Franklin Gothic Heavy", 20));
		painter.setPen(color);
		painter.drawText(playerTable, Qt::AlignCenter, tableText);
	}

}

void Game::on_exitButton_clicked()
{
	emit finished();
}
