#include "Registration.h"

#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	Registration r;
	r.show();
	
	//Player p1("Andrei", Player::Color::Blue);
	//Player p2("Adi", Player::Color::Red);
	//Player p3("Player3", Player::Color::Green);
	//Player p4("Player4", Player::Color::Yellow);
	//std::vector<Player> players = { p1, p2, p3, p4 };
	//Game* game = new Game(players, p1);
	//game->show();
	
    return QApplication::exec();
}
