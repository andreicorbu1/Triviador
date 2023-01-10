#include "MainMenu.h"

MainMenu::MainMenu(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_user.SetUsername("No name");
	m_user.SetId(-1);
}

MainMenu::MainMenu(const User& user, QWidget* parent) :
	QWidget(parent),
	m_user(user)
{
	ui.setupUi(this);
}

MainMenu::~MainMenu()
{
	// empty
}

void MainMenu::hiMessage(const std::string& playerName)
{
	QString message = "Salut, ";
	message += playerName.c_str();
	ui.hiMessage->setText(message);
}

bool MainMenu::CheckGameCanStart()
{
	auto res = cpr::Put
	(
		cpr::Url{ "http://localhost:18080/newgame" }
	);
	return res.status_code == 200;
}

void MainMenu::StartLobby(std::string lobbyID)
{
	m_lobby = new Lobby(lobbyID, m_user.GetUsername());
	m_lobby->show();
	hide();
	connect(m_lobby, SIGNAL(finished()), this, SLOT(on_lobbyFinished()));
}

void MainMenu::Show()
{
	showMaximized();
}

void MainMenu::on_myProfileButton_clicked()
{
	this->ui.stackedWidget->setCurrentWidget(ui.myProfile);
	ShowPlayerHistory();
}

void MainMenu::on_creditsButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.credits);
}

void MainMenu::on_playButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.play);
}

void MainMenu::on_joinButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.joinGame);
}

void MainMenu::on_joinLobbyButton_clicked()
{
	std::string lobbyId = this->ui.lineEdit->text().toUtf8().constData();
	auto res = cpr::Put
	(
		cpr::Url{ "http://localhost:18080/addplayertolobby" },
		cpr::Body{ "id=" + lobbyId + "&" + "username=" + m_user.GetUsername() }
	);

	if (res.status_code == 200)
	{
		StartLobby(lobbyId);
	}
	else if (res.status_code == 401)
	{
		QMessageBox msgBox;
		msgBox.setText("Lobby is full");
		msgBox.exec();
	}
	else if (res.status_code == 400)
	{
		QMessageBox msgBox;
		msgBox.setText("Lobby not found");
		msgBox.exec();
	}
}

void MainMenu::on_createButton_clicked()
{
	auto res = cpr::Get
	(
		cpr::Url{ "http://localhost:18080/newlobby" },
		cpr::Body{ "username=" + m_user.GetUsername() }
	);

	try
	{
		auto id = crow::json::load(res.text);
		int lobbyId = id["lobby_id"].i();

		StartLobby(std::to_string(lobbyId));
	}
	catch (std::exception ex)
	{
		qDebug() << "Can't create new lobby";
	}
}

void MainMenu::on_logOutButton_clicked()
{
	close();
	Registration* registration = new Registration;
	registration->show();

	qDebug() << "Log Out button clicked";
}

void MainMenu::on_lobbyFinished()
{
	Show();
	m_lobby->close();
	delete m_lobby;
}

void MainMenu::ShowPlayerHistory()
{
	auto getPlayerHistory = cpr::Get
	(
		cpr::Url{ "http://localhost:18080/playerhistory" },
		cpr::Body{ "username=" + m_user.GetUsername() }
	);
	try
	{
		auto playerHistory = crow::json::load(getPlayerHistory.text);
		int line = 0;
		int column = 0;
		for (size_t i = 0; i < playerHistory.size(); i++)
		{
			int score = playerHistory[i]["score"].i();
			int rank = playerHistory[i]["rank"].i();

			auto* playerHistoryLabel{ static_cast<QLabel*>(ui.playerHistoryGrid->itemAtPosition(line, column)->widget()) };
			playerHistoryLabel->setText("Score: " + QString::number(score) + " Rank: " + QString::number(rank));
			column++;
			if (column > 1)
			{
				column = 0;
				line++;
			}
		}
	}
	catch (std::exception ex)
	{
		qDebug() << "Can't show matches history!";
	}
}
