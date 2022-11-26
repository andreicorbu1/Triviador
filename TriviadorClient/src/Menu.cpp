#include "Menu.h"

Menu::Menu()
{
	ui.setupUi(this);

}

void Menu::hiMessage(std::string playerName)
{
	QString message = "Salut, " + QString::fromStdString(playerName);
	ui.hiMessage->setText(message);
}
