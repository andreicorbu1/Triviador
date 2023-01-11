#include "Registration.h"

#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	Registration r;
	r.show();
	
	//Player p1("Andrei", Player::Color::Blue);
	//Player p2("Adi", Player::Color::Red);
	//std::vector<Player> players = { p1, p2 };
	//Game* game = new Game(players, p1);
	//game->show();
	
    return QApplication::exec();
}
