#include "Registration.h"
#include "MainMenu.h"

#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    MainMenu w;
    w.Show();

    return QApplication::exec();
}
