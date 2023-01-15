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

void Lobby::on_leaveLobbyButton_clicked()
{
	auto res = cpr::Get
	(
		cpr::Url{ "http://25.65.182.120:18080/lobby/removeplayer" },
		cpr::Body{ "id=" + m_lobbyID + "&" + "username=" + m_currentPlayer.GetName() }
	);
	
	emit finished();
}

void Lobby::on_startGameButton_clicked()
{
	auto res = cpr::Put
	(
		cpr::Url{ "http://25.65.182.120:18080/lobby/creategame" }
	);
}

void Lobby::on_gameFinished()
{
	m_game->close();
	delete m_game;
	on_leaveLobbyButton_clicked();
}

void Lobby::LobbyLoop()
{
	int waitingTime = 0;
	
	auto playersFromLobby = cpr::Get
	(
		cpr::Url{ "http://25.65.182.120:18080/lobby/players" },
		cpr::Body{ "id=" + m_lobbyID }
	);
	
	if (playersFromLobby.status_code != 200)
	{
		return;
	}
	
	HideAllPlayersName();
	m_players.clear();
	QPainter painter(this);
	auto players = crow::json::load(playersFromLobby.text);
	for (size_t i = 0; i < players.size(); i++)
	{
		std::string name = players[i]["name"].s();
		std::string color = players[i]["color"].s();
		m_playersLabel[i]->setText(QString::fromUtf8(name));
		m_playersLabel[i]->show();
		m_players.emplace_back(name, Player::ToColor(color));
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
		cpr::Url{ "http://25.65.182.120:18080/lobby/waiting" },
		cpr::Body{ "id=" + m_lobbyID }
	);

	if (res.status_code == 410)
	{
		QMessageBox msgBox;
		msgBox.setText("Lobby waiting time has expired");
		msgBox.exec();
		on_leaveLobbyButton_clicked();
		return;
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
