#include "Lobby.h"

Lobby::Lobby(const std::string& lobbyID, const std::string& username, QWidget* parent) :
	m_lobbyID(lobbyID)
{
	ui.setupUi(this);
	ui.lobbyID_label->setText(QString::fromUtf8("ID: " + lobbyID));
	ui.startGameButton->hide();
	m_currentPlayer = Player(username, Player::Color::None);

	HideAllPlayersName();

	SetPlayersLabel();

	QTimer::singleShot(0, this, SLOT(LobbyLoop()));
}

Lobby::~Lobby()
{}

void Lobby::closeEvent(QCloseEvent* event)
{
	//on_leaveLobbyButton_clicked();
}

void Lobby::on_leaveLobbyButton_clicked()
{
	auto res = cpr::Get
	(
		cpr::Url{ "http://localhost:18080/removeplayerfromlobby" },
		cpr::Body{ "id=" + m_lobbyID + "&" + "username=" + m_currentPlayer.GetName() }
	);
	emit finished();
}

void Lobby::on_startGameButton_clicked()
{
	auto res = cpr::Put
	(
		cpr::Url{ "http://localhost:18080/newgame" }
	);
}

void Lobby::on_gameFinished()
{
	qDebug() << "Here";
	m_game->close();
	delete m_game;
	on_leaveLobbyButton_clicked();
}

void Lobby::LobbyLoop()
{
	int waitingTime = 0;
	QPainter painter(this);
	auto playersFromLobby = cpr::Get
	(
		cpr::Url{ "http://localhost:18080/getplayersfromlobby" },
		cpr::Body{ "id=" + m_lobbyID }
	);
	HideAllPlayersName();
	m_players.clear();
	auto players = crow::json::load(playersFromLobby.text);
	for (size_t i = 0; i < players.size(); i++)
	{
		std::string name = players[i]["name"].s();
		std::string color = players[i]["color"].s();
		m_playersLabel[i]->setText(QString::fromUtf8(name));
		m_playersLabel[i]->show();
		m_players.push_back(Player(name, Player::ToColor(color)));
	}
	if (m_players.size() > 1)
	{
		ui.startGameButton->show();
	}
	else
	{
		ui.startGameButton->hide();
	}

	auto res = cpr::Get
	(
		cpr::Url{ "http://localhost:18080/waitinginlobby" },
		cpr::Body{ "id=" + m_lobbyID }
	);

	if (res.status_code == 410)
	{
		QMessageBox msgBox;
		msgBox.setText("Lobby waiting time has expired");
		msgBox.exec();
		on_leaveLobbyButton_clicked();
	}
	else if (res.status_code == 300)
	{
		this->hide();
		StartGame();
		return;
	}
	
	QTimer::singleShot(2000, this, SLOT(LobbyLoop()));
}

void Lobby::HideAllPlayersName()
{
	ui.player1->hide();
	ui.player2->hide();
	ui.player3->hide();
	ui.player4->hide();
}

void Lobby::SetPlayersLabel()
{
	m_playersLabel.push_back(ui.player1);
	m_playersLabel.push_back(ui.player2);
	m_playersLabel.push_back(ui.player3);
	m_playersLabel.push_back(ui.player4);
}

void Lobby::StartGame()
{
	m_game = new Game(m_players, m_currentPlayer, this);
	m_game->show();
	hide();
	connect(m_game, SIGNAL(finished()), this, SLOT(on_gameFinished()));
}
