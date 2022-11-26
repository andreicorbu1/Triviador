#include "Registration.h"
#include "Menu.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menu menu;
    Registration registration;
    registration.show();
    menu.showMaximized();
    
    return QApplication::exec();
}
