#include "Registration.h"
#include "MainMenu.h"
#include "Player.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    Player abc;
    QApplication a(argc, argv);
    MainMenu mainMenu;
    Registration registration;
    registration.show();
    mainMenu.hiMessage(abc.GetName());
    mainMenu.showMaximized();

    
    return QApplication::exec();
}
