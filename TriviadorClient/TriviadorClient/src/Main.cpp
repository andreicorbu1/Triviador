#include "Registration.h"
#include "Game.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

	// TEST
	/*Player currentPlayer("Player1", Player::Color::Green);
	std::vector<Player> players = { currentPlayer, Player("Player2", Player::Color::Red), Player("Player3", Player::Color::Blue), Player("Player4", Player::Color::Yellow) };
	players[0].SetScore(1000);
	players[1].SetScore(4000);
	players[2].SetScore(3000);
	players[3].SetScore(2500);
	Game game(players, currentPlayer);
	game.showMaximized();*/
	Registration r;
	r.show();

    return QApplication::exec();
}
