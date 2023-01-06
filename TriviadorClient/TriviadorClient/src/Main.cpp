#include "Registration.h"
#include "Game.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

	// TEST
	std::vector<Player> players = { Player("Player1", Player::Color::Green), Player("Player2", Player::Color::Red), Player("Player3", Player::Color::Blue), Player("Player4", Player::Color::Yellow) };
	Game game(players);
	game.showMaximized();

    return QApplication::exec();
}
