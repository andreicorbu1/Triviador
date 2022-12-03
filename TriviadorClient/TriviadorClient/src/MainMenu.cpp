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

void MainMenu::on_twoPlayersButton_clicked()
{
    Player a("cristian", Player::Color::Blue);
    Player b("tibi", Player::Color::Red);
    Game* game = new Game(a, b, this);
    game->showMaximized();
}



void MainMenu::Show()
{
    showMaximized();
}

void MainMenu::on_logOutButton_clicked()
{
    close();
    Registration* registration = new Registration;
    registration->show();

    qDebug() << "Log Out button clicked";
}