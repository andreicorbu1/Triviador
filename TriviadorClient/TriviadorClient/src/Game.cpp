#include "Game.h"

Game::Game(QWidget* parent)
	: m_questionWindow(QuestionWindow(this))
	, m_board(Board(1, 1))
{
	setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	ui.setupUi(this);
	SetBackground();
}

Game::Game(std::vector<Player>& players, Player currentPlayer, QWidget* parent)
	: m_questionWindow(QuestionWindow(this))
	, m_players(players)
	, m_currentPlayer(currentPlayer)
{
	setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
	ui.setupUi(this);
	SetBackground();
	m_signalMapper = new QSignalMapper(this);
	m_questionWindow.SetCurrentPlayer(m_currentPlayer);

	switch (m_players.size())
	{
	case 2:
		m_board = Board(3, 3, this);
		m_board.Set2PGame();
		break;
	case 3:
		m_board = Board(5, 3, this);
		m_board.Set3PGame();
		break;
	case 4:
		m_board = Board(6, 4, this);
		m_board.Set4PGame();
		break;
	default:
		break;
	}
	ConnectButtons();

	QTimer::singleShot(1000, this, SLOT(GameLoop()));
	ui.stageLabel->hide();
}

Game::~Game()
{
	// empt
}

void Game::ShowQuestion(QuestionType type)
{
	m_questionWindow.SetQuestionType(type);
	m_questionWindow.FetchQuestion(m_players);
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

void Game::UpdateBoard()
{
	auto res = cpr::Get
	(
		cpr::Url{ "http://localhost:18080/getboard" },
		cpr::Body{"username="+m_currentPlayer.GetName()}
	);

	if (res.status_code == 200)
	{
		auto board = crow::json::load(res.text);
		for (int i = 0; i < m_board.Size(); i++)
		{
			Player player = Player(board[i]["owner"]["name"].s(), Player::GetColor(board[i]["owner"]["color"].s()));
			int score = board[i]["score"].i();
			
			m_board[i].SetOwner(player);
			m_board[i].SetScore(score);
			m_board[i].Update();
		}
	}
}

void Game::UpdatePlayerScores()
{
	auto res = cpr::Get(cpr::Url{ "http://localhost:18080/getplayersfromgame" });

	if (res.status_code == 200)
	{
		auto players = crow::json::load(res.text);
		for (auto& player : players)
		{
			auto name = player["name"].s();
			auto score = player["score"].i();
			for (auto& p : m_players)
			{
				if (p.GetName() == name)
				{
					p.SetScore(score);
				}
			}
		}
	}
}

void Game::AddPlayersHistory()
{
	auto copyOfPlayers(m_players);
	std::ranges::sort(copyOfPlayers, std::less());
	for (size_t i = 0; i < copyOfPlayers.size(); i++)
	{
		AddPlayerHistory(copyOfPlayers[i], i);
	}
}

void Game::AddPlayerHistory(Player& player, int rank)
{
	auto res = cpr::Put
	(
		cpr::Url{ "http://localhost:18080/addplayerhistory" },
		cpr::Body{ "id=" + std::to_string(m_ID) + "&username=" + player.GetName() +
		"&score=" + std::to_string(player.GetScore()) + "&rank=" + std::to_string(rank) }
	);
	if (res.status_code == 400)
	{
		qDebug() << "Cannot add player history!";
	}
}

void Game::GameLoop()
{
	int waitingTime = 0;
	auto res = cpr::Get
	(
		cpr::Url{ "http://localhost:18080/stage" },
		cpr::Body{ "username=" + m_currentPlayer.GetName() }
	);

	if (res.status_code == 200)
	{
		data = crow::json::load(res.text);
		if (data["stage"] == "wait")
		{
			ui.stageLabel->hide();
			waitingTime = 2000;
		}
		if (data["stage"] == "numericalAnswerQuestion")
		{
			ui.stageLabel->hide();
			waitingTime = 16000;
			ShowQuestion(QuestionType::NumericalAnswer);
		}
		else if (data["stage"] == "multipleAnswerQuestion")
		{
			ui.stageLabel->hide();
			waitingTime = 16000;
			ShowQuestion(QuestionType::MultipleAnswer);
		}
		else if (data["stage"] == "chooseBase")
		{
			ui.stageLabel->setText("Choose a base!");
			ui.stageLabel->show();
			waitingTime = 2000;
			//choose base
		}
		else if (data["stage"] == "chooseTerritory")
		{
			ui.stageLabel->setText("Choose your territories!");
			ui.stageLabel->show();
			waitingTime = 2000;
			//choose base
		}

		else if (data["stage"] == "attack")
		{
			ui.stageLabel->hide();
			waitingTime = 2000;
			// attack
		}
		else if (data["stage"] == "update")
		{
			ui.stageLabel->hide();
			UpdateBoard();
			waitingTime = 2000;
			UpdatePlayerScores();
		}
		else if (data["stage"] == "result")
		{
			m_resultWindow = new ResultWindow(m_players, this);
			m_resultWindow->show();
			connect(m_resultWindow, SIGNAL(backToMenu()), this, SLOT(on_gameFinished()));
			return;
		}
		else
		{
			waitingTime = 2000;
		}
	}
	else
	{
		waitingTime = 3000;
	}
	
	QTimer::singleShot(waitingTime, this, SLOT(GameLoop()));
}

void Game::on_gameFinished()
{
	emit finished();
}

void Game::action(int position)
{
	qDebug() << "The Button " << position << " was clicked!";
	if (data["stage"] == "chooseBase" || data["stage"] == "chooseTerritory")
	{
		std::string isBase = "0";
		if (data["stage"] == "chooseBase")
		{
			isBase = "1";
		}
		auto res = cpr::Put
		(
			cpr::Url{ "http://localhost:18080/choose" },
			cpr::Body{ "username=" + m_currentPlayer.GetName() + "&position=" + std::to_string(position) + "&isBase=" + isBase }
		);
	}
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
		QString tableText = ((m_players[i].GetName() == m_currentPlayer.GetName() ? "You" : m_players[i].GetName()) + " " + std::to_string(m_players[i].GetScore())).c_str();
		painter.setFont(QFont("Franklin Gothic Heavy", 20));
		painter.setPen(color);
		painter.drawText(playerTable, Qt::AlignCenter, tableText);
	}
}

void Game::on_exitButton_clicked()
{
	on_gameFinished();
}
