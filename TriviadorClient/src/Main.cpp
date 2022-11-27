#include "Registration.h"
#include "Player.h"
#include "MainMenu.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    Player abc;
    QApplication a(argc, argv);
    Registration registration;
    MainMenu menu;
    //registration.show();
    menu.showMaximized();


    
    return QApplication::exec();
}
