#include "MainMenu.h"

MainMenu::MainMenu(QWidget* parent)
	: QWidget(parent)
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

void MainMenu::StartGame(std::vector<Player>& players)
{
	m_game = new Game(players, this);
	m_game->show();
	hide();
	connect(m_game, SIGNAL(finished()), this, SLOT(on_gameFinished()));
}

void MainMenu::Show()
{
	showMaximized();
}

void MainMenu::on_myProfileButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.myProfile);
}

void MainMenu::on_creditsButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.credits);
}

void MainMenu::on_playButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.play);
}

void MainMenu::on_createGameButton_clicked() const
{
	this->ui.stackedWidget->setCurrentWidget(ui.createGame);
}

void MainMenu::on_backButton_clicked()
{
	this->ui.stackedWidget->setCurrentWidget(ui.play);
}

void MainMenu::on_logOutButton_clicked()
{
	close();
	Registration* registration = new Registration;
	registration->show();

	qDebug() << "Log Out button clicked";
}

void MainMenu::on_twoPlayersButton_clicked()
{
	Player a("cristian", Player::Color::Blue);
	Player b("tibi", Player::Color::Red);
	std::vector<Player> players = { a, b };
	StartGame(players);
}

void MainMenu::on_threePlayersButton_clicked()
{
	Player a("cristian", Player::Color::Blue);
	Player b("tibi", Player::Color::Red);
	Player c("adi", Player::Color::Yellow);
	std::vector<Player> players = { a, b, c };
	StartGame(players);
}

void MainMenu::on_fourPlayersButton_clicked()
{
	Player a("cristian", Player::Color::Blue);
	Player b("tibi", Player::Color::Red);
	Player c("adi", Player::Color::Yellow);
	Player d("andrei", Player::Color::Green);
	std::vector<Player> players = { a, b, c, d };
	StartGame(players);
}

void MainMenu::on_gameFinished()
{
	Show();
	m_game->close();
	delete m_game;
}