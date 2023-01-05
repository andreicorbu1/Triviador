#include "Lobby.h"

Lobby::Lobby(const std::string& lobbyID, const std::string& username, QWidget* parent) :
	m_lobbyID(lobbyID)
{
	ui.setupUi(this);
	ui.lobbyID_label->setText(QString::fromUtf8("Lobby ID: " + lobbyID));

	m_currentPlayer = Player(username, Player::Color::None);

	HideAllPlayersName();

	SetPlayersLabel();

	setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);
	this->setWindowState(Qt::WindowMaximized);
}

Lobby::~Lobby()
{}

void Lobby::on_leaveLobbyButton_clicked()
{
	auto res = cpr::Get
	(
		cpr::Url{ "http://localhost:18080/removeplayerfromlobby" },
		cpr::Body{ "id=" + m_lobbyID + "&" + "username=" + m_currentPlayer.GetName() }
	);
	if (res.status_code == 200)
	{
		emit finished();
	}
}

void Lobby::on_startGameButton_clicked()
{
	auto res = cpr::Put
	(
		cpr::Url{ "http://localhost:18080/newgame" }
	);
	if (res.status_code == 200)
	{
		this->hide();
		StartGame();
	}
}

void Lobby::paintEvent(QPaintEvent* paintEvent)
{
	QPainter painter(this);
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
	}

	auto playersFromLobby = cpr::Get
	(
		cpr::Url{ "http://localhost:18080/getplayersfromlobby" },
		cpr::Body{ "id=" + m_lobbyID }
	);

	m_players.clear();
	auto players = crow::json::load(playersFromLobby.text);
	for (size_t i = 0; i < players.size(); i++)
	{
		std::string name = players[i]["name"].s();
		std::string color = players[i]["color"].s();
		m_playersLabel[i]->setText(QString::fromUtf8(name));
		m_playersLabel[i]->show();
		m_players.push_back(Player(name, Player::GetColor(color)));
	}
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
	m_game = new Game(m_players, this);
	m_game->show();
	hide();
	connect(m_game, SIGNAL(finished()), this, SLOT(on_lobbyFinished()()));
}
